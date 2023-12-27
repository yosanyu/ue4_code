// Fill out your copyright notice in the Description page of Project Settings.


#include "DiscipleEvent.h"
#include "HandleEquipment.h"
#include "HandleDisciple.h"

void UDiscipleEvent::StartEvent(USect* sect) {
	for (int32 i = 0; i < sect->disciples.Num(); i++)
		DoEvent(sect, i);

	int32 index = 0;
	int32 times = sect->disciples.Num();
	for (int32 i = 0; i < times; i++) {
		if (sect->disciples[index].death) {
			gDisHealth += sect->disciples[index].health;
			gDisAttack += sect->disciples[index].attack;
			gDisDefense += sect->disciples[index].defense;
			++gDisDeath;
			UHandleDisciple::Expel(sect, index);
		}
		else
			++index;
	}
}

void UDiscipleEvent::DoEvent(USect* sect, int32& index) {
	GetEquipmentEvent(sect, index);
	WifeEvent(sect, index);
	SexyEvent(sect, index);
	EatEilxir(sect, index);
	LifeTreasureEvent(sect, index);
	StarSoulEvent(sect, index);
	DeathEvent(sect, index);
}

void UDiscipleEvent::GetEquipmentEvent(USect* sect, int32& index) {
	int32 random = FMath::FRandRange(1, 100);
	// 事件觸發機率
	// 5
	if (random <= 5 + gExploreEvent) {
		int32 row = 0;
		FEquipment temp;
		int32 p = FMath::FRandRange(1, 100);

		// 仙級
		if (p <= 5) {
			temp.CreateByRarity(EItemRarityType::Immortal);
			row = FMath::FRandRange(0, 10);
		}

		// 聖級
		else if (p <= 15) {
			temp.CreateByRarity(EItemRarityType::Holy);
			row = FMath::FRandRange(11, 21);
		}

		// 天級 40
		else if (p <= 40) {
			temp.CreateByRarity(EItemRarityType::Sky);
			row = FMath::FRandRange(22, 32);
		}
		// 確定得到後加入資料 40
		if (p <= 40) {
			if (UHandleEquipment::CanAddEquipment(sect, temp.type))
				UHandleEquipment::AddSingleEquipment(sect, temp);
			else
				sect->AddSpiritStone(temp.price);

			if (temp.rarity == EItemRarityType::Immortal)
				sect->steamAchievement.CheckEquipmentAchievement();

			FText message = UEventMessage::GetEqupment(sect->disciples[index], temp, row);
			sect->chanceLogs.Emplace(message);
		}
	}
}

void UDiscipleEvent::DeathEvent(USect* sect, int32& index) {
	int32 random = FMath::FRandRange(1, 1000);
	// 事件觸發機率 0.1%
	if (random <= 7 + gExploreEvent) {
		int32 p = FMath::FRandRange(1, 100);
		FText message = FText();
		int32 row = 0;
		// 死亡
		if (p <= 70) {
			row = FMath::FRandRange(0, 6);
			sect->disciples[index].death = true;
		}
		// 沒死
		else
			row = 7;

		message = UEventMessage::GetDeath(sect->disciples[index], row);
		sect->chanceLogs.Emplace(message);
	}
}

void UDiscipleEvent::WifeEvent(USect* sect, int32& index) {
	if (UHandleDisciple::IsMarried(sect->disciples[index])) {
		if (FMath::RandRange(1, 1000) <= 10 + gExploreEvent)
			DivorceEvent(sect, index);
	}

	else {
		if (FMath::RandRange(1, 1000) <= 10 + gExploreEvent)
			MarryEvent(sect, index);
	}
}

void UDiscipleEvent::DivorceEvent(USect* sect, int32& index) {
	UHandleDisciple::Divorce(sect, index);
	FText message = UEventMessage::GetWifeEvent(sect->disciples[index], FMath::RandRange(0, 4));
	sect->chanceLogs.Emplace(message);
}

void UDiscipleEvent::MarryEvent(USect* sect, int32& index) {
	FWife wife;
	wife.Create();
	UHandleDisciple::Marry(sect, index, wife);
	FText message = UEventMessage::GetWifeEvent(sect->disciples[index], 5);
	sect->chanceLogs.Emplace(message);
}

void UDiscipleEvent::SexyEvent(USect* sect, int32& index) {
	if (UHandleDisciple::IsMarried(sect->disciples[index])) {
		if (FMath::RandRange(1, 100) <= 5 + gSexEvent) {
			TArray<int32> a;
			for (int32 i = 0; i < 3; i++)
				a.Emplace(FMath::RandRange(50, 100));
			sect->disciples[index].AddAttribute(a[0], a[1], a[2]);
			//FText message = UEventMessage::GetWifeEvent(sect->disciples[index], 6);
			//sect->chanceLogs.Emplace(message);
		}
	}
}

void UDiscipleEvent::LifeTreasureEvent(USect* sect, int32& index) {
	// 2
	if (FMath::RandRange(1, 100) > 2 + gExploreEvent)
		return;

	TArray<int32> had;
	
	for (auto& i : sect->disciples[index].lifeTreasures) {
		if (i.id > 0)
			had.Emplace(i.id);
		else
			break;
	}
	
	// 命寶滿了
	if (had.Num() == sect->disciples[index].lifePalace)
		return;
	had.Sort([](const int32& A, const int32& B) {
		return A < B;
	});
	const char* path = "DataTable'/Game/DataTable/Treasures/LifeTreasures.LifeTreasures'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames;

	if (pDataTable != NULL)
		rowNames = pDataTable->GetRowNames();
	else
		return;

	int32 count = 0;
	for (auto& i : had) {
		rowNames.RemoveAt(i - count - 1);
		++count;
	}
	
	int32 which = FMath::RandRange(0, rowNames.Num() - 1);
	FCommonAttribute* data = pDataTable->FindRow<FCommonAttribute>(rowNames[which], "");
	//sect->disciples[index].lifeTreasures[had.Num()] = *data;
	sect->disciples[index].SetLifeTreasure(had.Num(), *data);
	FText message = UEventMessage::GetLifeTreasure(sect->disciples[index], index, data->name);
	sect->disciples[index].cultivateSpeed++;
	sect->chanceLogs.Emplace(message);
}

void UDiscipleEvent::StarSoulEvent(USect* sect, int32& index) {
	// 2
	if (FMath::RandRange(1, 100) > 2 + gExploreEvent)
		return;

	TArray<int32> had;

	for (auto& i : sect->disciples[index].starSouls) {
		if (i.id > 0)
			had.Emplace(i.id);
		else
			break;
	}

	// 星魂滿了
	if (had.Num() == sect->disciples[index].star)
		return;
	had.Sort([](const int32& A, const int32& B) {
		return A < B;
	});
	const char* path = "DataTable'/Game/DataTable/Treasures/StarSoul.StarSoul'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rowNames;

	if (pDataTable != NULL)
		rowNames = pDataTable->GetRowNames();
	else
		return;

	int32 count = 0;
	for (auto& i : had) {
		rowNames.RemoveAt(i - count - 1);
		++count;
	}

	int32 which = FMath::RandRange(0, rowNames.Num() - 1);
	FStarSoul* data = pDataTable->FindRow<FStarSoul>(rowNames[which], "");
	//sect->disciples[index].starSouls[had.Num()] = *data;
	sect->disciples[index].SetStarSoul(had.Num(), *data);
	FText message = UEventMessage::GetStarSoul(sect->disciples[index], index, data->name);
	sect->chanceLogs.Emplace(message);
	sect->disciples[index].cultivateSpeed++;
}

void UDiscipleEvent::EatEilxir(USect* sect, int32& index) {
	for (int32 eat = 0; eat < 10; eat++) {
		if (UHandleDisciple::CanUseElixirs(sect->disciples[index])) {
			int32 random;
			if (sect->disciples[index].rarity > EDiscipleRarityType::Genius)
				random = FMath::RandRange(0, 49);
			else
				random = FMath::RandRange(50, 75);
			FElixirs temp;
			int32 j = 0;
			for (auto& elem : sect->elixirs) {
				if (j == random) {
					temp = elem.Key;
					break;
				}
				j++;
			}
			UHandleDisciple::UseElixirs(sect, index, temp);
		}
		else
			break;
	}
}

FText UEventMessage::GetEqupment(const FDisciple& dis, const FEquipment& e, int32 index) {
	FString str = "";
	FString name = dis.surname.ToString();
	if (gLanguage == 0) {
		name.Append(" ");
	}
	name.Append(dis.name.ToString());
	TArray<FStringFormatArg> args = {
		FStringFormatArg(name), FStringFormatArg(e.attribute.name.ToString()) 
	};
	const char* path = "DataTable'/Game/DataTable/Message/ChanceGetEquip.ChanceGetEquip'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FName row = FName(*FString::FromInt(index));
		FReadText* data = pDataTable->FindRow<FReadText>(row, "");
		if (data != NULL) {
			str = *data->str.ToString();
			str = str.Format(*str, args);
			return FText::FromString(*str);
		}
	}
	return FText();
}

FText UEventMessage::GetDeath(const FDisciple& dis, int32 index) {
	FString str = "";
	FString name = dis.surname.ToString();
	if (gLanguage == 0) {
		name.Append(" ");
	}
	name.Append(dis.name.ToString());
	TArray<FStringFormatArg> args = {FStringFormatArg(name)};
	const char* path = "DataTable'/Game/DataTable/Message/DIsDeath.DIsDeath'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FName row = FName(*FString::FromInt(index));
		FReadText* data = pDataTable->FindRow<FReadText>(row, "");
		if (data != NULL) {
			str = *data->str.ToString();
			str = str.Format(*str, args);
			return FText::FromString(*str);
		}
	}
	return FText();
}

FText UEventMessage::GetWifeEvent(const FDisciple& dis, int32 index) {
	FString str = "";
	TArray<FStringFormatArg> args = { 
		FStringFormatArg(dis.surname.ToString()),
		FStringFormatArg(dis.name.ToString()) 
	};
	const char* path = "DataTable'/Game/DataTable/Message/ChanceWife.ChanceWife'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FName row = FName(*FString::FromInt(index));
		FReadText* data = pDataTable->FindRow<FReadText>(row, "");
		if (data != NULL) {
			str = *data->str.ToString();
			str = str.Format(*str, args);
			return FText::FromString(*str);
		}
	}
	return FText();
}

FText UEventMessage::GetLifeTreasure(FDisciple& dis, int32 index, FText name) {
	FString str1 = "";
	FString str2 = "";
	str1 = Read(24);
	str2 = Read(25);
	TArray<FStringFormatArg> arg1 = {
		FStringFormatArg(dis.year), FStringFormatArg(name.ToString())
	};
	TArray<FStringFormatArg> arg2 = {
		FStringFormatArg(dis.surname.ToString()),
		FStringFormatArg(dis.name.ToString()),
		FStringFormatArg(name.ToString())
	};
	str1 = str1.Format(*str1, arg1);
	dis.logs.Emplace(FText::FromString(*str1));
	str2 = str2.Format(*str2, arg2);
	return FText::FromString(*str2);
}

FText UEventMessage::GetStarSoul(FDisciple& dis, int32 index, FText name) {
	FString str1 = "";
	FString str2 = "";
	str1 = Read(26);
	str2 = Read(27);
	TArray<FStringFormatArg> arg1 = {
		FStringFormatArg(dis.year), FStringFormatArg(name.ToString())
	};
	TArray<FStringFormatArg> arg2 = {
		FStringFormatArg(dis.surname.ToString()),
		FStringFormatArg(dis.name.ToString()),
		FStringFormatArg(name.ToString())
	};
	str1 = str1.Format(*str1, arg1);
	dis.logs.Emplace(FText::FromString(*str1));
	str2 = str2.Format(*str2, arg2);
	return FText::FromString(*str2);
}
