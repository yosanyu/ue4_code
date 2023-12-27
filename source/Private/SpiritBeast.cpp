// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiritBeast.h"

FPassiveSkill::FPassiveSkill() {

}

FSpiritBeast::FSpiritBeast() {
	
}

void FSpiritBeast::SetPassive() {
	const char* path = "DataTable'/Game/DataTable/SpiritBeast/PassiveSkill.PassiveSkill'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		int32 which = FMath::RandRange(0, rowNames.Num() - 1);
		FPassiveSkill* data = pDataTable->FindRow<FPassiveSkill>(rowNames[which], "");
		if (data != NULL) {
			passive = *data;
		}
	}
}

void FSpiritBeast::Setting() {
	age = FMath::RandRange(1, 200);
	if (age < 30)
		growing = EGrowing::Childhood;
	else if (age < 80)
		growing = EGrowing::Growth;
	else if (age < 200)
		growing = EGrowing::Maturity;
	else
		growing = EGrowing::Old;

	TArray<int32> p = {1, 8, 20, 40, 65, 100};
	int32 random = FMath::RandRange(1, 100);
	for (int32 i = 0; i < p.Num(); i++) {
		if (random <= p[i]) {
			blood = EBlood(i);
			break;
		}
	}
}

void FSpiritBeast::Growth() {
	++age;
	if (age == 30)
		growing = EGrowing::Growth;
	else if (age == 80)
		growing = EGrowing::Maturity;
	else if (age == 200)
		growing = EGrowing::Old;

}

bool FSpiritBeast::IsDeath() {
	if (id > 0 && id < 10)
		return false;
	return age > 400 ? true : false;
}

float FSpiritBeast::GetBuff() {
	TArray<float> bBuff = { 0.5, 0.4, 0.3, 0.2, 0.1, 0.0 };
	TArray<float> gbuff = { 0.2, 0, 0.2, 0.7 };
	if (id > 0 && id < 10)
		return bBuff[uint8(blood)];
	return bBuff[uint8(blood)] - gbuff[uint8(growing)];
}
