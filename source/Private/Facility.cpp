// Fill out your copyright notice in the Description page of Project Settings.


#include "Facility.h"

FFacility::FFacility() {

}

int32 FFacility::GetLevelUpCost() {
	// 靈石花費每一等+1000
	return (level + 1) * 1000;
}

bool FFacility::IsLevelMax() {
	//return level == 10 ? true : false;
	return level == 10;
}

void FFacility::LevelUp() {
	++level;
	hasLevelUp = true;
}

void FFacility::Update() {
	hasLevelUp = false;
}

FDefenseFacility::FDefenseFacility() {
	missleNum = 0;
	missleProduction = 5000;
	missleAttack = 5;
	const char* path = "DataTable'/Game/DataTable/Facility/tower.tower'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& row : rowNames) {
			FTower* data = pDataTable->FindRow<FTower>(row, "");
			if (data != NULL)
				towers.Emplace(*data);
		}
	}
}

void FDefenseFacility::MakeMissle() {
	int32 max = 100000;
	if (missleNum + missleProduction > max)
		missleNum = max;
	else
		missleNum += missleProduction;
}

int32 FTower::GetDamage() {
	return level * attack;
}

