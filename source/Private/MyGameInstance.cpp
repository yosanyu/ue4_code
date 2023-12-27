// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\MyGameInstance.h"
#include "..\Public\Constant.h"
#include "HandleDisciple.h"
#include "HandleEquipment.h"
#include "HandleSpiritBeast.h"
#include "HandleBody.h"
#include "HandleShop.h"
#include "DiscipleEvent.h"

UMyGameInstance::UMyGameInstance() {
}

void UMyGameInstance::Create() {
	gSectBuff = 0.0;
	gDisDeath = 0;
	gDisHealth = 0;
	gDisAttack = 0;
	gDisDefense = 0;
	gMapLevel = 0;
	SetYear(1);
	sect = NewObject<USect>(this, TEXT("sect"));
	
	for (int32 i = 0; i < 10; i++)
		UHandleDisciple::AddDisciple(sect);

	sect->shop.disTimes = 0;

	for (int32 i = 0; i < 30; i++) // 30
		UHandleEquipment::AddEquipment(sect);
	for (int32 i = 0; i < 10; i++) // 10
		UHandleSpiritBeast::AddSpiritBeast(sect);
	for (int32 i = 0; i < 10; i++) // 10
		UHandleBody::AddOrgan(sect);
	CreateEnemy();
	sect->steamAchievement.ResetData();

}

void UMyGameInstance::CreateEnemy() {
	int32 sectNum = FMath::RandRange(15, 30);
	const char* path = "DataTable'/Game/DataTable/name/SectName.SectName'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable == NULL)
		return;
	TArray<FName> rows = pDataTable->GetRowNames();

	FString objectName = "Enemy";
	for (int32 i = 0; i < sectNum; i++) {
		FString temp = objectName;
		int32 rowIndex = FMath::RandRange(0, rows.Num() - 1);
		FReadText* data = pDataTable->FindRow<FReadText>(rows[rowIndex], "");
		if (data == NULL)
			continue;
		rows.RemoveAt(rowIndex);
		temp.AppendInt(i);
		UEnemySect* eSect = NewObject<UEnemySect>(this, FName(*temp));
		eSect->Create();
		eSect->name = data->str;
		enemys.Emplace(eSect);
	}

	int32 demonNum = FMath::RandRange(15, 20);
	for (int32 i = 0; i < demonNum; i++) {
		FDemon temp;
		temp.Create();
		demons.Emplace(temp);
	}
}

void UMyGameInstance::LoadSect(FSaveSect save, FString name) {
	sect = NewObject<USect>(this, FName(*name));
	sect->Load(save);
}

void UMyGameInstance::LoadESect(TArray<FSaveESect> save, TArray<FString> name) {
	for (int32 i = 0; i < save.Num(); i++) {
		UEnemySect* eSect = NewObject<UEnemySect>(this, FName(*name[i]));
		eSect->Load(save[i]);
		enemys.Emplace(eSect);
	}
}

void UMyGameInstance::LoadSetting(FSettingSave save) {
	//SetYear(year);
	//gSectBuff = sectBuff;
	//gDisP = disP;
	SetYear(save.year);
	gSectBuff = save.gSectBuff;
	gSectHBuff = save.gSectHBuff;
	gSectABuff = save.gSectABuff;
	gSectDBuff = save.gSectDBuff;
	gSBBuff = save.gSBBuff;
	gTechCost = save.gTechCost;
	gYSpiritStoneMin = save.gYSpiritStoneMin;
	gYSpiritStoneMax = save.gYSpiritStoneMax;
	gYSpiritStonePer = save.gYSpiritStonePer;
	gMapLevel = save.gMapLevel;
	gDisDeath = save.gDisDeath;
	gDisHealth = save.gDisHealth;
	gDisAttack = save.gDisAttack;
	gDisDefense = save.gDisDefense;
	gDisP = save.gDisP;
	gEquipP = save.gEquipP;
	gSexEvent = save.gSexEvent;
	gExploreEvent = save.gExploreEvent;
	gLanguage = save.gLanguage;
	gIgnoreDefense = save.gIgnoreDefense;
	gReduceDamage = save.gReduceDamage;
	gFriendly = save.gFriendly;
}

FSettingSave UMyGameInstance::SaveSetting() {
	FSettingSave save;
	save.year = GetYear();
	save.gSectBuff = gSectBuff;
	save.gSectHBuff = gSectHBuff;
	save.gSectABuff = gSectABuff;
	save.gSectDBuff = gSectDBuff;
	save.gSBBuff = gSBBuff;
	save.gTechCost = gTechCost;
	save.gYSpiritStoneMin = gYSpiritStoneMin;
	save.gYSpiritStoneMax = gYSpiritStoneMax;
	save.gYSpiritStonePer = gYSpiritStonePer;
	save.gMapLevel = gMapLevel;
	save.gDisDeath = gDisDeath;
	save.gDisHealth = gDisHealth;
	save.gDisAttack = gDisAttack;
	save.gDisDefense = gDisDefense;
	save.gDisP = gDisP;
	save.gEquipP = gEquipP;
	save.gSexEvent = gSexEvent;
	save.gExploreEvent = gExploreEvent;
	save.gLanguage = gLanguage;
	save.gIgnoreDefense = gIgnoreDefense;
	save.gReduceDamage = gReduceDamage;
	save.gFriendly = gFriendly;
	return save;
}

void UMyGameInstance::LoadDisDeath(TArray<int32> values) {
	gDisDeath = values[0];
	gDisHealth = values[1];
	gDisAttack = values[2];
	gDisDefense = values[3];
}

void UMyGameInstance::AfterYear() {
	UDiscipleEvent::StartEvent(sect);
	sect->Update();
	for (auto& i : enemys) {
		i->Update();
		if (i->IsAnnexed()) {
			// 經營附庸
			if (sect->ideas[5]) {
				sect->AddSpiritStone(FMath::RandRange(5000, 10000) * (gMapLevel + 1) * 1.1);
				sect->AddMedicinalMaterials(FMath::RandRange(1000, 2000) * (gMapLevel + 1) * 1.1);
			}
			else {
				sect->AddSpiritStone(FMath::RandRange(5000, 10000) * (gMapLevel + 1));
				sect->AddMedicinalMaterials(FMath::RandRange(1000, 2000) * (gMapLevel + 1));
			}
		}
		// 改善關係
		//if (sect->ideas[4])
		i->AddFriendly(gFriendly);
	}

	// 系統每年簽到獲取3件裝備
	for (int32 i = 0; i < 3; i++)
		UHandleEquipment::AddEquipment(sect);

	AfterAYear();
}

int32 UMyGameInstance::GetYear() {
	return GetNowYear();
}

float UMyGameInstance::GetSectBuff() {
	return gSectBuff;
}

UEnemySect* UMyGameInstance::GetEnemy(int32 index) {
	return enemys[index];
}

void UMyGameInstance::DealSect(int32 winOrLose) {
	switch (eSectMode)
	{
	case 0:
		AnnexSect(winOrLose);
		break;
	case 1:
		EliminateSect(winOrLose);
		break;
	case 2:
		Defense(winOrLose);
		break;
	default:
		break;
	}
}

void UMyGameInstance::AnnexSect(int32 winOrLose) {
	int32 index = 0;
	FText eName = enemys[enemyIndex]->name;
	if (winOrLose == 1 || winOrLose == 3) {
		index = 7;
		enemys[enemyIndex]->friendly = 0;
	}

	else {
		index = 8;
		enemys[enemyIndex]->hadAnnexed = true;
		UHandleSectSystem::UseAttack(sect);
		sect->AddExp(500);
		++sect->toMapESect;
		sect->steamAchievement.CheckEliminateAchievement();
	}
	sect->logs.Emplace(FormatBattleMessage(eName, index));
}

void UMyGameInstance::EliminateSect(int32 winOrLose) {
	int32 index = 0;
	FText eName = enemys[enemyIndex]->name;
	if (winOrLose == 1 || winOrLose == 3)
		index = 9;
	else {
		index = 10;
		for (int32 i = 0; i < 20; i++)
			UHandleEquipment::AddEquipment(sect);
		enemys.RemoveAt(enemyIndex);
		UHandleSectSystem::UseAttack(sect);
		sect->AddExp(500);
		++sect->toMapESect;
		sect->steamAchievement.CheckEliminateAchievement();
	}
	sect->logs.Emplace(FormatBattleMessage(eName, index));
}

void UMyGameInstance::Defense(int32 winOrLose) {
	FText eName = enemys[enemyIndex]->name;
	if (winOrLose == 1 || winOrLose == 3) {
		int32 loss = sect->spiritStone * 0.1;
		sect->spiritStone -= loss;
		sect->logs.Emplace(FormatFailedMessage(eName, 12, loss));
		if (enemys[enemyIndex]->hadAnnexed)
			enemys[enemyIndex]->hadAnnexed = false;
	}
	else {
		sect->AddSpiritStone(FMath::RandRange(1000, 5000));
		sect->logs.Emplace(FormatBattleMessage(eName, 11));
	}
	enemys[enemyIndex]->friendly = 0;
}

void UMyGameInstance::RemoveDemon() {
	demons.RemoveAt(demonIndex);
	sect->AddExp(500);
	++sect->toMapDemon;
}

bool UMyGameInstance::CanGoToNewMap() {
	if (gMapLevel == 6)
		return false;
	return sect->toMapESect >= 10 && sect->toMapDemon >= 5;
}

void UMyGameInstance::ToNewMap() {
	if (gMapLevel < 6) {
		++gMapLevel;
		enemys.Empty();
		demons.Empty();
		CreateEnemy();
	}
}

bool UMyGameInstance::IsEnding() {
	return gMapLevel == 6;
}

void UMyGameInstance::SetLanguage(int32 which) {
	gLanguage = which;
}

int32 UMyGameInstance::GetLanguage() {
	return gLanguage;
}
