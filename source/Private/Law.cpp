// Fill out your copyright notice in the Description page of Project Settings.


#include "Law.h"

FLaw::FLaw() {
	id = 9999;
	name = FText();
	health = 0;
	attack = 0;
	defense = 0;
	rarity = EItemRarityType::Immortal;
	exp = 0;
	lawLevel = 0;
}

void FLaw::SetPrice() {
	switch (rarity)
	{
	case EItemRarityType::Immortal:
		price = 50000;
		break;
	case EItemRarityType::Holy:
		price = 25000;
		break;
	case EItemRarityType::Sky:
		price = 8000;
		break;
	case EItemRarityType::Earth:
		price = 5000;
		break;
	case EItemRarityType::Mysterious:
		price = 1500;
		break;
	case EItemRarityType::Yellow:
		price = 500;
		break;
	case EItemRarityType::Human:
		price = 200;
		break;
	default:
		break;
	}
}

void FLaw::LevelUp() {
	while (exp >= GetNextExp() && CanLevelUp()) {
		exp -= GetNextExp();
		++lawLevel;
	}
}

bool FLaw::CanLevelUp() {
	return lawLevel == 10 ? false : true;
}

int32 FLaw::GetNextExp() {
	TArray<int32> exps = { 10, 30, 100, 200, 300, 400, 500, 600, 800, 1000, 0 };
	return exps[lawLevel];
}

