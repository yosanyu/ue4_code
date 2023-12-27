// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Constant.h"
#include "Engine/DataTable.h"

FEquipAffix::FEquipAffix() {
	affix = EAffix::None;
	value = 0;
	buff = 0.0;
}

void FEquipAffix::Create() {
	TArray<int32> p = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 95, 100 };
	int random = FMath::RandRange(1, 100);
	for (int32 i = 0; i < p.Num(); i++) {
		if (random <= p[i]) {
			affix = EAffix(i);
			break;
		}
	}
	switch (affix)
	{
	case EAffix::Health:
		IsHealth();
		break;
	case EAffix::Attack:
		IsAttack();
		break;
	case EAffix::Defense:
		IsDefense();
	case EAffix::H5:
		IsH5();
		break;
	case EAffix::A5:
		IsA5();
		break;
	case EAffix::D5:
		IsD5();
		break;
	case EAffix::HP:
		IsHP();
		break;
	case EAffix::AP:
		IsAP();
		break;
	case EAffix::DP:
		IsDP();
		break;
	case EAffix::CriticalP:
		IsCP();
		break;
	case EAffix::CriticalStrike:
		IsCS();
		break;
	case EAffix::None:
		break;
	default:
		break;
	}
}

void FEquipAffix::CreateUnique(EItemRarityType rarity) {
	TArray<int32> p = { 32, 64, 96, 100};
	int random = FMath::RandRange(1, 100);
	for (int32 i = 0; i < p.Num(); i++) {
		if (random <= p[i]) {
			affix = EAffix(i+11);
			break;
		}
	}
	if (rarity == EItemRarityType::Holy) {
		value = FMath::RandRange(10, 15);
	}
	else if (rarity == EItemRarityType::Immortal)
		value = FMath::RandRange(16, 25);

}

void FEquipAffix::OrganAffix() {
	int random = FMath::RandRange(0, 2);
	affix = EAffix(random);
	switch (affix)
	{
	case EAffix::Health:
		IsHealth();
		break;
	case EAffix::Attack:
		IsAttack();
		break;
	case EAffix::Defense:
		IsDefense();
	default:
		break;
	}
}

void FEquipAffix::IsHealth() {
	TArray<int32> p = { 10, 35, 65, 100 };
	int32 random = FMath::RandRange(1, 100);
	affix = EAffix::Health;
	if (random <= p[0])
		value = FMath::RandRange(1000, 1500);
	else if(random <= p[1])
		value = FMath::RandRange(700, 1000);
	else if (random <= p[2])
		value = FMath::RandRange(400, 700);
	else
		value = FMath::RandRange(50, 400);
}

void FEquipAffix::IsAttack() {
	TArray<int32> p = { 25, 60, 100 };
	int32 random = FMath::RandRange(1, 100);
	affix = EAffix::Attack;
	if (random <= p[0])
		value = FMath::RandRange(400, 600);
	else if (random <= p[1])
		value = FMath::RandRange(250, 400);
	else
		value = FMath::RandRange(100, 250);
}

void FEquipAffix::IsDefense() {
	TArray<int32> p = { 25, 60, 100 };
	int32 random = FMath::RandRange(1, 100);
	affix = EAffix::Defense;
	if (random <= p[0])
		value = FMath::RandRange(300, 400);
	else if (random <= p[1])
		value = FMath::RandRange(200, 300);
	else
		value = FMath::RandRange(100, 200);
}

void FEquipAffix::IsH5() {
	affix = EAffix::H5;
	value = FMath::RandRange(1, 100);
}

void FEquipAffix::IsA5() {
	affix = EAffix::A5;
	value = FMath::RandRange(1, 100);
}

void FEquipAffix::IsD5() {
	affix = EAffix::D5;
	value = FMath::RandRange(1, 100);
}

void FEquipAffix::IsHP() {
	affix = EAffix::HP;
	int32 random = FMath::RandRange(10, 25);
	buff = float(random) / 100.0f;
}

void FEquipAffix::IsAP() {
	affix = EAffix::AP;
	int32 random = FMath::RandRange(10, 25);
	buff = float(random) / 100.0f;
}

void FEquipAffix::IsDP() {
	affix = EAffix::DP;
	int32 random = FMath::RandRange(10, 25);
	buff = float(random) / 100.0f;
}

void FEquipAffix::IsCP() {
	affix = EAffix::CriticalP;
	value = FMath::RandRange(1, 10);
}

void FEquipAffix::IsCS() {
	affix = EAffix::CriticalStrike;
	//TArray<float> p = { 0.01, 0.02, 0.03, 0.04, 0.05 };
	//int32 random = FMath::RandRange(0, 4);
	//buff = p[random];
	int32 random = FMath::RandRange(1, 10);
	buff = float(random) / 100.0f;
}

FEquipment::FEquipment() {
	type = EEquipmentType::Weapon;
	rarity = EItemRarityType::Immortal;
	affix.Empty();
}

void FEquipment::Create() {
	DicideType();
	DecideRarity();
	DicidePrice();
	ReadTable();
	DecideAffix();
}

void FEquipment::Create(EEquipmentType eType, EItemRarityType r, int32 eLevel) {
	type = eType;
	rarity = r;
	ReadTable();
	DecideAffix();
	enhanceLevel = eLevel;
}

void FEquipment::CreateByRarity(EItemRarityType r) {
	DicideType();
	rarity = r;
	ReadTable();
	DecideAffix();
	enhanceLevel = 0;
}

int32 FEquipment::GetHealth() {
	int value = FMath::RoundToInt(float(attribute.health) * (1.0 + enhanceLevel * 0.05));
	value += GetValue(EAffix::Health);
	return value;
}

int32 FEquipment::GetAttack() {
	int value = FMath::RoundToInt(float(attribute.attack) * (1.0 + enhanceLevel * 0.05));
	value += GetValue(EAffix::Attack);
	return value;
}

int32 FEquipment::GetDefense() {
	int value = FMath::RoundToInt(float(attribute.defense) * (1.0 + enhanceLevel * 0.05));
	value += GetValue(EAffix::Defense);
	return value;
}

int32 FEquipment::GetH5() {
	return GetValue(EAffix::H5);
}

int32 FEquipment::GetA5() {
	return GetValue(EAffix::A5);
}

int32 FEquipment::GetD5() {
	return GetValue(EAffix::D5);
}

float FEquipment::GetHP() {
	return GetBuff(EAffix::HP);
	return 0.0f;
}

float FEquipment::GetAP() {
	return GetBuff(EAffix::AP);
}

float FEquipment::GetDP() {
	return GetBuff(EAffix::DP);
}

int32 FEquipment::GetCP() {
	return GetValue(EAffix::CriticalP);
}

float FEquipment::GetCS() {
	return GetBuff(EAffix::CriticalStrike);
}

int32 FEquipment::GetValue(EAffix buffType) {
	int32 value = 0;
	for (auto& i : affix) {
		if (i.affix == buffType)
			value += i.value;
	}
	return value;
}

float FEquipment::GetBuff(EAffix buffType) {
	float buff = 0.0;
	for (auto& i : affix) {
		if (i.affix == buffType)
			buff += i.buff;
	}
	return buff;
}

void FEquipment::DicideType() {
	int32 random = FMath::RandRange(0, 2);
	switch (random)
	{
	case 0:
		type = EEquipmentType::Weapon;
		break;
	case 1:
		type = EEquipmentType::Artifact;
		break;
	case 2:
		type = EEquipmentType::HiddenWeapon;
		break;
	default:
		break;
	}
}

void FEquipment::DecideRarity() {
	int32 p = gEquipP;
	TArray<int32> rarityP = {1, 4, 9, 17, 31, 55, 100};
	rarityP[0] += p;
	for (int32 i = 1; i < 6; i++)
		rarityP[i] += p * 2;

	int32 random = FMath::RandRange(1, 100);
	int32 choice = 0;
	for (int32 i = 0; i < rarityP.Num(); i++) {
		if (random <= rarityP[i]) {
			choice = i;
			break;
		}
	}
	switch (choice)
	{
	case 0:
		rarity = EItemRarityType::Immortal;
		break;
	case 1:
		rarity = EItemRarityType::Holy;
		break;
	case 2:
		rarity = EItemRarityType::Sky;
		break;
	case 3:
		rarity = EItemRarityType::Earth;
		break;
	case 4:
		rarity = EItemRarityType::Mysterious;
		break;
	case 5:
		rarity = EItemRarityType::Yellow;
		break;
	case 6:
		rarity = EItemRarityType::Human;
	default:
		break;
	}
}

void FEquipment::DicidePrice() {
	TArray<int32> prices = { 20000, 15000, 12000, 8000, 4000, 1000, 500 };
	int32 index = uint8(rarity);
	int32 min = prices[index] * 0.9;
	int max = prices[index] * 1.1;
	price = FMath::RandRange(min, max);
}

void FEquipment::ReadTable() {
	TArray<FString> paths;
	switch (type)
	{
	case EEquipmentType::Weapon:
		paths = GetWeaponPath();
		break;
	case EEquipmentType::Artifact:
		paths = GetArtifactPath();
		break;
	case EEquipmentType::HiddenWeapon:
		paths = GetHiddenWeaponPath();
		break;
	default:
		break;
	}
	
	FString temp = paths[uint8(rarity)];
	const char* path = TCHAR_TO_ANSI(*temp);
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		int32 random = FMath::RandRange(0, rowNames.Num() - 1);
		FName row = FName(*FString::FromInt(random));
		FCommonAttribute* data = pDataTable->FindRow<FCommonAttribute>(row, "");
		if (data != NULL) {
			attribute = *data;
		}
	}
	
}

void FEquipment::DecideAffix() {
	affix.Empty();
	bool isUnique = rarity == EItemRarityType::Holy || rarity == EItemRarityType::Immortal;
	for (int32 i = 0; i < 8 - uint8(rarity); i++) {
		FEquipAffix temp;
		if(isUnique && i == 0) {
			temp.CreateUnique(rarity);
		}
		else {
			temp.Create();
		}
		affix.Emplace(temp);
	}
}

bool FEquipment::IsMaxLevel() {
	TArray<int32> level = { 10, 15, 20, 25, 30, 35 , 40 };
	if (enhanceLevel < level[uint8(rarity)])
		return true;
	else
		return false;
}

bool FEquipment::LevelUp(int32& spiritStone) {
	TArray<int32> costs = { 1200, 700, 450, 350, 200, 150 , 100 };
	TArray<int32> prices = { 960, 560, 360, 280, 160, 120 , 80 };
	spiritStone -= costs[uint8(rarity)];
	int32 random = FMath::RandRange(1, 100);
	if (random <= 80) {
		++enhanceLevel;
		price += prices[uint8(rarity)];
		return true;
	}
	else
		return false;
}

