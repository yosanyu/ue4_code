// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleFacility.h"
#include "Constant.h"

bool UHandleFacility::IsOpen(FFacility facility) {
	return facility.isOpen;
}

bool UHandleFacility::HasLevelUp(FFacility facility) {
	return facility.hasLevelUp;
}

int32 UHandleFacility::GetLevelUpCost(FFacility facility) {
	// 獲取升級花費
	return facility.GetLevelUpCost();
}

bool UHandleFacility::CanLevelUp(USect* sect, int32 index) {
	int32 cash = sect->spiritStone;
	FFacility temp = sect->facilities[index];
	// 錢夠且設施還沒滿等
	if (cash >= temp.GetLevelUpCost() && !temp.IsLevelMax())
		return true;
	else
		return false;
}

void UHandleFacility::LevelUp(USect* sect, int32 index) {
	sect->spiritStone -= sect->facilities[index].GetLevelUpCost();
	sect->facilities[index].LevelUp();
	if (sect->facilities[index].IsLevelMax()) {
		sect->sectSystem.lottery += 3;
	}
	switch (index)
	{
	case 0:
		sect->ySpiritStone += sect->facilities[index].value;
		break;
	case 1:
		sect->yMedicinalMaterials += sect->facilities[index].value;
		break;
	case 2:
		sect->facilities[index].value -= 50;
		break;
	case 3:
		sect->ySpiritStone += sect->facilities[index].value;
		break;
	case 4:
		sect->discipleMax += sect->facilities[index].value;
		break;
	case 5:
		sect->speed += sect->facilities[index].value;
		break;
	case 6:
		gSectBuff += 0.01;
		break;
	case 7:
		break;
	case 8:
		sect->ySpiritStone += sect->facilities[index].value;
		break;
	case 9:
		sect->ySpiritStone += sect->facilities[index].value;
		break;
	default:
		break;
	}
	sect->logs.Emplace(UFacilityMessage::LevelUp(sect, sect->facilities[index]));
	sect->steamAchievement.CheckFacilityAchievement(sect->facilities);
}

int32 UHandleFacility::HowManyCanMake(USect* sect, FFacility facility) {
	int32 cost = facility.value;
	return sect->medicinalMaterials / cost;
}

float UHandleFacility::GetPercent() {
	return gSectBuff * 100;
}

int32 UHandleFacility::GetFHealth() {
	return gDisHealth;
}

int32 UHandleFacility::GetFAttack() {
	return gDisAttack;
}

int32 UHandleFacility::GetFDefense() {
	return gDisDefense;
}

FText UFacilityMessage::LevelUp(USect* sect, const FFacility& facility) {
	FString str = "";
	TArray<FStringFormatArg> args = { 
		FStringFormatArg(facility.name.ToString()),
		FStringFormatArg(facility.level)
	};
	str = str.Format(*ReadSectMessage(0), args);
	return FText::FromString(*str);
}

FText UHandleFacility::FormatEffect(const FFacility& facility, int32 index) {
	FString str = "";
	int32 which = 0;
	switch (index)
	{
	case 0:
		which = 0;
		break;
	case 1:
		which = 1;
		break;
	case 2:
		which = 2;
		break;
	case 3:
		which = 0;
		break;
	case 4:
		which = 3;
		break;
	case 5:
		which = 4;
		break;
	case 6:
		which = 5;
		break;
	case 8:
		which = 0;
		break;
	case 9:
		which = 0;
		break;
	case 10:
		which = 6;
		break;
	default:
		break;
	}

	TArray<FStringFormatArg> args;
	if (which == 2)
		args.Emplace(FStringFormatArg(facility.value));
	else
		args.Emplace(FStringFormatArg(facility.value * facility.level));
	
	const char* path = "DataTable'/Game/DataTable/Facility/FacilityEffect.FacilityEffect'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		FReadText* data = pDataTable->FindRow<FReadText>(rowNames[which], "");
		if (data != NULL)
			str = data->str.ToString();
	}

	str = str.Format(*str, args);
	return FText::FromString(*str);
}

int32 UHandleFacility::GetDisDeath() {
	return gDisDeath;
}

bool UHandleFacility::CanTowerLevelUp(USect* sect, int32 index) {
	int32 level = 0;
	switch (index)
	{
	case 0:
		level = 5;
		break;
	case 1:
		level = 8;
		break;
	case 2:
		level = 10;
		break;
	default:
		break;
	}

	if (sect->defenseFacility.towers[index].level < level)
		return true;
	return false;
}

void UHandleFacility::TowerLevelUp(USect* sect, int32 index) {
	++sect->defenseFacility.towers[index].level;
	sect->spiritStone -= sect->defenseFacility.towers[index].price;
}

bool UHandleBook::CanBuyBook(USect* sect) {
	if (sect->noGetBooks.Num() == 0 || sect->spiritStone < 4000)
		return false;
	else
		return true;
}

void UHandleBook::BuyBook(USect* sect) {
	sect->spiritStone -= 4000;
	sect->AddBook();
}
