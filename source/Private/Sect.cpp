// Fill out your copyright notice in the Description page of Project Settings.


#include "Sect.h"
#include "HandleDisciple.h"
#include "HandleEquipment.h"
#include "HandleBody.h"

USect::USect() {
	ReadLaws();
	ReadTreasures();
	ReadBuildings();
	spiritStone = 100000; // 100000
	medicinalMaterials = 10000; // 10000 gCostMax
	//health = 1000000000;
	//attack = 1000000000;
	//defense = 1000000000;
	ReadFacility();
	ReadElixirs();
	ReadElders();
	ReadBooks();
	shop.UpdateGood(noGetLaws);
	for (int32 i = 0; i < 6; i++)
		ideas.Emplace(false);
}

void USect::ReadLaws() {
	const char* path = "DataTable'/Game/DataTable/Law/Law.Law'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FLaw* temp = pDataTable->FindRow<FLaw>(i, "");
			if (temp != NULL) {
				temp->SetPrice();
				noGetLaws.Emplace(*temp);
			}
		}
	}
	// 20
	//int32 size = noGetLaws.Num();
	for (int32 i = 0; i < 20; i++) {
		int32 random = FMath::RandRange(0, noGetLaws.Num() - 1);
		hadLaws.Emplace(noGetLaws[random]);
		noGetLaws.RemoveAt(random);
	}
		
}

void USect::ReadTreasures() {
	const char* path = "DataTable'/Game/DataTable/Treasures/Treasure.Treasure'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FTreasure* temp = pDataTable->FindRow<FTreasure>(i, "");
			if (temp != NULL)
				noGetTreasures.Emplace(*temp);
		}
	}
	/*
	int32 size = noGetTreasures.Num();
	for (int32 i = 0; i < size;i++) {
		AddTreasure();
	}
	*/
}

void USect::ReadBuildings() {
	const char* path = "DataTable'/Game/DataTable/Treasures/Buildings.Buildings'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FBuilding* temp = pDataTable->FindRow<FBuilding>(i, "");
			if (temp != NULL)
				noGetBuilding.Emplace(*temp);
		}
	}
	/*
	int32 size = noGetBuilding.Num();
	for (int32 i = 0; i < size; i++) {
		hadBuilding.Emplace(noGetBuilding[0]);
		noGetBuilding.RemoveAt(0);
	}
	*/
}

void USect::ReadFacility() {
	const char* path = "DataTable'/Game/DataTable/Facility/Facility.Facility'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FFacility* temp = pDataTable->FindRow<FFacility>(i, "");
			if (temp != NULL)
				facilities.Emplace(*temp);
		}
	}
}

void USect::ReadElixirs() {
	const char* path = "DataTable'/Game/DataTable/Elixir/Elixirs.Elixirs'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FElixirs* temp = pDataTable->FindRow<FElixirs>(i, "");
			if (temp != NULL)
				elixirs.Emplace(*temp, 2);
		}
	}
}

void USect::ReadElders() {
	const char* path = "DataTable'/Game/DataTable/Elder/Elder.Elder'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FElder* temp = pDataTable->FindRow<FElder>(i, "");
			if (temp != NULL)
				elders.Emplace(*temp);
		}
	}
}

void USect::ReadBooks() {
	const char* path = "DataTable'/Game/DataTable/Treasures/Books.Books'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : rowNames) {
			FBook* temp = pDataTable->FindRow<FBook>(i, "");
			if (temp != NULL)
				noGetBooks.Emplace(*temp);
		}
	}
}

void USect::AddTreasure() {
	if (noGetTreasures.Num() == 0) // 已經沒寶物可獲得了
		return;

	int32 random = FMath::RandRange(0, noGetTreasures.Num() - 1);
	FTreasure t = noGetTreasures[random];
	noGetTreasures.RemoveAt(random);

	switch (t.type) // 根據類型調整相對應效果
	{
	case ESectValue::SpiritStone:
		ySpiritStone += t.value;
		break;
	case ESectValue::MedicinalMaterials:
		yMedicinalMaterials += t.value;
		break;
	case ESectValue::Health:
		health += t.value;
		break;
	case ESectValue::Attack:
		attack += t.value;
		break;
	case ESectValue::Defense:
		defense += t.value;
		break;
	case ESectValue::Speed:
		speed += t.value;
		break;
	case ESectValue::SexyEvent:
		gSexEvent += t.value;
		break;
	default:
		break;
	}
	
	hadTreasure.Emplace(t);
	int32 num = hadTreasure.Num();
	steamAchievement.ChcekTreasureAchievement(num);
	steamAchievement.SpecificTreasureAchievement(t.id);
	steamAchievement.ChcekDemonAchievement(num);
}

TArray<int32> USect::GetFiveDisIndex() {
	TArray<int32> num;
	TArray<int32> index;
	for (int32 i = 0; i < disciples.Num(); i++)
		num.Add(i);

	for (int32 i = 0; i < 5; i++) {
		int32 random = FMath::RandRange(0, num.Num() - 1);
		index.Add(num[random]);
		num.RemoveAt(random);
	}
	return index;
}

TArray<FDisciple> USect::GetFiveDis(TArray<int32> index) {
	TArray<FDisciple> dis;
	for (int32 i = 0; i < 5; i++)
		dis.Emplace(disciples[index[i]]);
	return dis;
}

TArray<FText> USect::Explore() {
	// 獲取裝備
	int32 eNums = FMath::RandRange(3, 8);
	TArray<FEquipment> equips;
	for (int32 i = 0; i < eNums; i++) {
		FEquipment temp;
		temp.Create();
		equips.Emplace(temp);
		if (UHandleEquipment::CanAddEquipment(this, temp.type))
			UHandleEquipment::AddSingleEquipment(this, temp);
		else
			AddSpiritStone(temp.price);
		if (temp.rarity == EItemRarityType::Immortal)
			steamAchievement.CheckEquipmentAchievement();
	}

	// 獲取丹藥
	int32 pNums = FMath::RandRange(15, 40);
	TMap<FElixirs, int32> pills;
	for (int32 i = 0; i < pNums; i++) {
		int32 j = 0;
		int32 whichElixir = FMath::RandRange(0, 76);
		for (auto& elem : elixirs) {
			if (j == whichElixir) {
				if (elem.Value < 100000)
					++elem.Value;
				int32* num = pills.Find(elem.Key);
				if (num == nullptr)
					pills.Emplace(elem.Key, 1);
				else
					*num += 1;		
				break;
			}
			j++;
		}
	}

	TArray<FText> message;

	// 讀表
	const char* path = "DataTable'/Game/DataTable/Message/ExploreMessage.ExploreMessage'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& i : equips) {
			int32 eRow = uint8(i.type) * 7 + uint8(i.rarity);
			TArray<FStringFormatArg> arg1 = { FStringFormatArg(i.attribute.name.ToString()) };
			FReadText* data = pDataTable->FindRow<FReadText>(rowNames[eRow], "");
			if (data != NULL) {
				FString str = data->str.ToString();
				str = FString::Format(*str, arg1);
				message.Add(FText::FromString(*str));
			}
		}
		FReadText* data = pDataTable->FindRow<FReadText>(rowNames[21], "");
		if (data != NULL) {
			for (auto& elem : pills) {
				TArray<FStringFormatArg> arg2 = { FStringFormatArg(elem.Key.name.ToString()),
												  FStringFormatArg(elem.Value)};
				FString str = data->str.ToString();
				str = FString::Format(*str, arg2);
				message.Add(FText::FromString(*str));
			}
		}
	}

	return message;

}

void USect::AddBook() {
	int32 random = FMath::RandRange(0, noGetBooks.Num() - 1);
	FBook temp = noGetBooks[random];
	noGetBooks.RemoveAt(random);
	hadBooks.Emplace(temp);
	EBookType type = temp.type;
	switch (type)
	{
	case EBookType::Health:
		health += temp.value;
		break;
	case EBookType::Damage:
		attack += temp.value;
		break;
	case EBookType::Defense:
		defense += temp.value;
		break;
	case EBookType::ALLAttribute:
		health += temp.value;
		attack += temp.value;
		defense += temp.value;
		break;
	case EBookType::SpiritStone:
		ySpiritStone += temp.value;
		break;
	case EBookType::MedicinalMaterials:
		yMedicinalMaterials += temp.value;
		break;
	case EBookType::Disciple:
		gSectBuff += (0.01 * temp.value);
		break;
	case EBookType::IgnoreDefense:
		gIgnoreDefense += (0.01 * temp.value);
		break;
	case EBookType::ReduceDamage:
		gReduceDamage += (0.01 * temp.value);
		break;
	case EBookType::Speed:
		speed += temp.value;
		break;
	case EBookType::TechnologyCost:
		gTechCost += (0.01 * temp.value);
		break;
	case EBookType::Friendly:
		gFriendly += temp.value;
		break;
	case EBookType::NoEffect:
		break;
	case EBookType::SpiritBeast:
		gSBBuff += (0.01 * temp.value);
	default:
		break;
	}
}

void USect::Update() {
	AddExp(100);
	UpdateDisciple();
	UpdateFacility();
	UpdateSpiritBeast();

	tree.levelupLimit = 0;
	defenseFacility.MakeMissle();
	AnnualIncome();
	shop.UpdateGood(noGetLaws);
}

void USect::AnnualIncome() {
	float buff = gYSpiritStonePer;
	float bMin = gYSpiritStoneMin;
	float bMax = gYSpiritStoneMax;

//	if (ideas[0])
//		buff += 0.05;
//	if (ideas[1]) {
//		bMin -= 0.15;
//		bMax += 0.15;
//	}

	int32 min = ySpiritStone * (buff + bMin + 1.0);
	int32 max = ySpiritStone * (buff + bMax + 1.0);
	AddSpiritStone(FMath::RandRange(min, max));
	AddMedicinalMaterials(yMedicinalMaterials);
}

void USect::UpdateDisciple() {
	int32 index = 0;
	int32 times = disciples.Num();
	for (int32 i = 0; i < times; i++) {
		++disciples[index].year;
		disciples[index].Update(speed);
		if (disciples[index].background == EBackground::Merchant)
			AddSpiritStone(1000);
		if (disciples[index].background == EBackground::OWVisit) {
			AddSpiritStone(500);
			AddMedicinalMaterials(500);
		}
		if (disciples[index].death) {
			gDisHealth += disciples[index].health;
			gDisAttack += disciples[index].attack;
			gDisDefense += disciples[index].defense;
			++gDisDeath;
			FString str = disciples[index].surname.ToString();
			if (gLanguage == 0) {
				str.Append(" ");
			}
			str.Append(disciples[index].name.ToString());
			FText name = FText::FromString(*str);
			logs.Emplace(FormatBattleMessage(name, 14));
			UHandleDisciple::Expel(this, index);
		}
		else
			++index;
	}
}

void USect::UpdateFacility() {
	for (auto& i : facilities)
		i.Update();
	int32 counts = facilities[10].value * facilities[10].level;
	for (int32 i = 0; i < counts; i++)
		UHandleBody::AddOrgan(this);
}

void USect::UpdateSpiritBeast() {
	int32 index = 0;
	int32 times = spiritBeasts.Num();
	for (int32 i = 0; i < times; i++) {
		spiritBeasts[index].Growth();
		if (spiritBeasts[index].IsDeath()) {
			logs.Emplace(FormatBattleMessage(spiritBeasts[index].name, 13));
			spiritBeasts.RemoveAt(index);
		}
		else
			++index;
	}
}

void USect::AddSpiritStone(int32 num) {
	if (spiritStone + num >= gCostMax)
		spiritStone = gCostMax;
	else
		spiritStone += num;
}

void USect::AddMedicinalMaterials(int32 num) {
	if (medicinalMaterials + num >= gCostMax)
		medicinalMaterials = gCostMax;
	else
		medicinalMaterials += num;
}

void USect::AddExp(int32 getExp) {
	if (level < 9) {
		exp += getExp;
		if (exp >= 1000) {
			++level;
			exp -= 1000;
		}
	}
}

void USect::BuildBuliding(int32 index) {
	spiritStone -= hadBuilding[index].price;
	hadBuilding[index].hasBuilded = true;
	FBuilding temp = hadBuilding[index];
	switch (temp.type)
	{
	case ESectValue::SpiritStone:
		ySpiritStone += temp.value;
		break;
	case ESectValue::MedicinalMaterials:
		yMedicinalMaterials += temp.value;
		break;
	case ESectValue::Health:
		health += temp.value;
		break;
	case ESectValue::Attack:
		attack += temp.value;
		break;
	case ESectValue::Defense:
		defense += temp.value;
		break;
	case ESectValue::Speed:
		speed += temp.value;
		break;
	case ESectValue::AttributePercent:
		gSectBuff = gSectBuff + 0.01 * temp.value;
		break;
	case ESectValue::AllAttribute:
		health += temp.value;
		attack += temp.value;
		defense += temp.value;
		break;
	default:
		break;
	}
	steamAchievement.ChcekBuildingAchievement();
}

FSaveSect USect::Save() {
	FSaveSect save;
	save.disciples = disciples;
	save.weapons = weapons;
	save.artifacts = artifacts;
	save.hiddenWeapons = hiddenWeapons;
	save.hadLaws = hadLaws;
	save.noGetLaws = noGetLaws;
	save.spiritBeasts = spiritBeasts;
	save.hadTreasure = hadTreasure;
	save.noGetTreasures = noGetTreasures;
	save.hadBuilding = hadBuilding;
	save.noGetBuilding = noGetBuilding;
	save.hadBooks = hadBooks;
	save.noGetBooks = noGetBooks;
	save.hands = hands;
	save.foots = foots;
	save.hearts = hearts;
	save.lungs = lungs;
	save.kidneys = kidneys;
	save.facilities = facilities;
	save.elixirs = elixirs;
	save.elders = elders;
	save.ideas = ideas;
	save.spiritStone = spiritStone;
	save.medicinalMaterials = medicinalMaterials;
	save.ySpiritStone = ySpiritStone;
	save.yMedicinalMaterials = yMedicinalMaterials;
	save.health = health;
	save.attack = attack;
	save.defense = defense;
	save.speed = speed;
	save.discipleMax = discipleMax;
	save.spiritBeastMax = spiritBeastMax;
	save.level = level;
	save.exp = exp;
	save.toMapESect = toMapESect;
	save.toMapDemon = toMapDemon;
	save.shop = shop;
	save.tree = tree;
	save.defenseFacility = defenseFacility;
	save.sectSystem = sectSystem;
	save.logs = logs;
	save.chanceLogs = chanceLogs;
	save.steamAchievement = steamAchievement;

	return save;
}

void USect::Load(FSaveSect save) {
	disciples = save.disciples;
	weapons = save.weapons;
	artifacts = save.artifacts;
	hiddenWeapons = save.hiddenWeapons;
	hadLaws = save.hadLaws;
	noGetLaws = save.noGetLaws;
	spiritBeasts = save.spiritBeasts;
	hadTreasure = save.hadTreasure;
	noGetTreasures = save.noGetTreasures;
	hadBuilding = save.hadBuilding;
	noGetBuilding = save.noGetBuilding;
	hadBooks = save.hadBooks;
	noGetBooks = save.noGetBooks;
	hands = save.hands;
	foots = save.foots;
	hearts = save.hearts;
	lungs = save.lungs;
	kidneys = save.kidneys;
	facilities = save.facilities;
	elixirs = save.elixirs;
	elders = save.elders;
	ideas = save.ideas;
	spiritStone = save.spiritStone;
	medicinalMaterials = save.medicinalMaterials;
	ySpiritStone = save.ySpiritStone;
	yMedicinalMaterials = save.yMedicinalMaterials;
	health = save.health;
	attack = save.attack;
	defense = save.defense;
	speed = save.speed;
	discipleMax = save.discipleMax;
	spiritBeastMax = save.spiritBeastMax;
	level = save.level;
	exp = save.exp;
	toMapESect = save.toMapESect;
	toMapDemon = save.toMapDemon;
	shop = save.shop;
	tree = save.tree;
	defenseFacility = save.defenseFacility;
	sectSystem = save.sectSystem;
	logs = save.logs;
	chanceLogs = save.chanceLogs;
	steamAchievement = save.steamAchievement;
}

TMap<FElixirs, int32> USect::MakeElixirs(int32 num) {
	int32 cost = facilities[2].value;
	medicinalMaterials = medicinalMaterials - cost * num;
	TMap<FElixirs, int32> made; // 煉製的丹藥
	// 丹藥機率
	TArray<int32> p = { 300, 600, 900, 1200 , 1500, 1800, 2050, 2300, 2550, 2800, 3050, 3300,
						3550, 3773, 3996 ,4196, 4396, 4596, 4796, 4996, 5183, 5343, 5503, 5663,
						5813, 5963, 6113, 6243, 6373, 6503, 6633, 6763, 6893, 7013, 7133, 7243,
						7353, 7463, 7573, 7683, 7793, 7903, 8003, 8098, 8193, 8288, 8383, 8478,
						8573, 8658, 8738, 8818, 8898, 8968, 9038, 9108, 9168, 9228, 9288, 9348,
						9408, 9468, 9502, 9536, 9570, 9600, 9630, 9655, 9680, 9700, 9720, 9740,
						9743, 9746, 9749, 9750, 10000 };
	// 讀表
	const char* path = "DataTable'/Game/DataTable/Elixir/Elixirs.Elixirs'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	// 讀得到表
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		// 煉製num顆
		for (int32 i = 0; i < num; i++) {
			// 這次機率
			steamAchievement.CheckPillsAchievement();
			int32 random = FMath::RandRange(1, 10000);
			for (int32 j = 0; j < p.Num(); j++) {
				if (random <= p[j]) {
					// 讀取丹藥資料
					FElixirs* temp = pDataTable->FindRow<FElixirs>(rowNames[j], "");
					if (temp != NULL) {
						int32* hadNums = elixirs.Find(*temp);
						if (hadNums != nullptr) {
							if (*hadNums < 100000)
							*hadNums += 1;
						}
						int32* make = made.Find(*temp);
						if (make == nullptr)
							made.Emplace(*temp, 1);
						else {
							if (*make < 100000)
								*make += 1;
						}
					}
					break;
				}
			}
		}
	}

	made.KeySort([](FElixirs A, FElixirs B) {
		return A.id < B.id;
	});

	return made;
}

bool HasNewData(const char* path, int32 num) {
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rows = pDataTable->GetRowNames();
	return rows.Num() > num;
}
