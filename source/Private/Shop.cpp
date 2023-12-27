// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "HandleSpiritBeast.h"
#include <thread>
//using std::thread;

FShop::FShop() {

}

void FShop::UpdateGood(TArray<FLaw> noGet) {
	updateTimes = 3;
	UpdateEquipments();
	UpdateLaws(noGet);
	spiritBeasts.Empty();

	for (int32 i = 0; i < 30; i++) {
		FSpiritBeast temp = UHandleSpiritBeast::CreateSB();
		spiritBeasts.Emplace(temp);
	}

	spiritBeasts.Sort([](const FSpiritBeast& A, const FSpiritBeast& B) {
		return A.id < B.id;
	});
}

void FShop::UpdateEquipments() {
	equips.Empty();

	for (int32 i = 0; i < 30; i++) {
		FEquipment temp;
		temp.Create();
		equips.Emplace(temp);
	}

	equips.Sort([](const FEquipment& A, const FEquipment& B) {
		if (A.type == B.type)
			return A.rarity < B.rarity;
		return A.type < B.type;
	});
}

void FShop::UpdateLaws(TArray<FLaw>& noGet) {
	laws.Empty();

	while (laws.Num() < 30 && noGet.Num() != 0) {
		int32 law = FMath::RandRange(0, noGet.Num() - 1);
		laws.Emplace(noGet[law]);
		noGet.RemoveAt(law);
	}

	laws.Sort([](const FLaw& A, const FLaw& B) {
		return A.id < B.id;
	});
}

FSectSystem::FSectSystem() {
	giftTimes = 0;
	alienateTimes = 0;
	exploreTimes = 0;
	attackTimes = 0;
	lottery = 5;
}

FBuilding::FBuilding() {
	id = 0;
	name = FText();
	effect = FText();
	value = 0;
	price = 0;
	hasBuilded = false;
	type = ESectValue::Attack;
}
