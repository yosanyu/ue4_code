// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonStruct.h"
#include "HandleAchievement.h"


FCommonAttribute::FCommonAttribute() {
	id = 0;
	name = FText();
	attack = 0;
	health = 0;
	defense = 0;
}

FStarSoul::FStarSoul() {
	id = 0;
	name = FText();
	value = 0;
	type = EAffix(0);
}


FAchievement::FAchievement() {
	//成就初始化
	achievements.SetNum(100);
	for (auto& i : achievements)
		i = EAchievementType::NoActivate;

	buildingNum = 0;
	disNum = -999;
	sonOfEraNum = -999;
	equipmentNum = -999;
	expelNum = 0;
	secretMethodNum = 0;
	gemNum = 0;
	pillsNum = 0;
	drawTimes = 0;
	giftTimes = 0;
	alienateTimes = 0;
	exploreTimes = 0;
	eliminateTimes = 0;
}

void FAchievement::ChcekTreasureAchievement(int32 num) {
	if (num > 100)
		return;

	TArray<int32> nums = { 1, 5, 20, 50, 100 };
	CheckAchievement(nums, num, 0);
}

void FAchievement::SpecificTreasureAchievement(int32 id) {
	if (TreasureAchievement::CanActiveSecretMethod(id, secretMethodNum)) {
		achievements[47] = EAchievementType::WaitActivate;
	}
	if (TreasureAchievement::CanActiveGem(id, gemNum)) {
		achievements[48] = EAchievementType::WaitActivate;
	}
}

void FAchievement::ChcekDemonAchievement(int32 num) {
	if (num > 100)
		return;

	TArray<int32> nums = { 1, 10, 50, 100 };
	CheckAchievement(nums, num, 5);
}

void FAchievement::ChcekBlueprintAchievement(int32 num) {
	if (num > 50)
		return;

	TArray<int32> nums = { 1, 5, 10, 20, 50 };
	/*
	int32 index = 0;
	if (nums.Find(num, index)) {
		if (achievements[index + 9] == EAchievementType::NoActivate)
			achievements[index + 9] = EAchievementType::WaitActivate;
	}
	*/
	CheckAchievement(nums, num, 9);
}

void FAchievement::ChcekBuildingAchievement() {
	if (buildingNum > 50) // 成就最高50
		return;

	++buildingNum;

	TArray<int32> nums = { 1, 5, 10, 20, 50 };
	CheckAchievement(nums, buildingNum, 14);
}

void FAchievement::ResetData() {
	disNum = 0;
	sonOfEraNum = 0;
	equipmentNum = 0;
}

void FAchievement::ChcekDiscipleAchievement(const EDiscipleRarityType& type) {
	if (disNum < 0 && sonOfEraNum < 0)
		return;

	if (disNum == 1000 && sonOfEraNum == 40) // 弟子與紀元之子成就都完成
		return;

	// 弟子成就
	if (disNum != 1000) {
		++disNum;
		TArray<int32> nums = { 1, 20, 50, 100, 500, 1000 };
		CheckAchievement(nums, disNum, 19);
	}

	// 紀元之子成就
	if (sonOfEraNum != 40 && type == EDiscipleRarityType::SonofEra) {
		++sonOfEraNum;
		TArray<int32> nums = { 1, 5, 10, 20, 40};
		CheckAchievement(nums, sonOfEraNum, 25);
	}
}

void FAchievement::CheckExpelDiscipleAchievement() {
	if (expelNum == 500)
		return;

	++expelNum;

	TArray<int32> nums = { 1, 10, 50, 100, 200, 500 };
	CheckAchievement(nums, expelNum, 30);
}

void FAchievement::CheckPillsAchievement() {
	if (pillsNum == 5000)
		return;

	++pillsNum;

	TArray<int32> nums = { 1, 100, 1000, 5000 };
	CheckAchievement(nums, pillsNum, 43);
}

void FAchievement::CheckEquipmentAchievement() {
	if (equipmentNum == 200)
		return;

	++equipmentNum;
	TArray<int32> nums = { 1, 5, 10, 20, 50, 100, 200 };
	CheckAchievement(nums, equipmentNum, 36);
}

void FAchievement::CheckDrawAchievement() {
	if (drawTimes == 200)
		return;

	++drawTimes;
	TArray<int32> nums = { 1, 10, 100, 200 };
	CheckAchievement(nums, drawTimes, 49);
}

void FAchievement::CheckTechnologyAchievement(const TArray<FTechnology>& branch, int32 mode) {
	auto IsMax = [&]() {
		int32 n = 0;
		for (auto& i : branch) {
			if (i.level == i.maxLevel)
				++n;
		}
		return n == branch.Num() ? true : false;
	};
	// 0是經濟 1是陣法 2是學派
	switch (mode) {
	case 0:
		if(IsMax())
			achievements[53] = EAchievementType::WaitActivate;
		break;
	case 1:
		if (IsMax())
			achievements[54] = EAchievementType::WaitActivate;
		break;
	case 2:
		if (IsMax())
			achievements[55] = EAchievementType::WaitActivate;
		break;
	default:
		break;
	}
}

void FAchievement::CheckElderAchievement(TArray<FElder>& elders) {
	int32 n = 0;
	for (auto& i : elders) {
		if (!i.IsLeveNotlMax())
			++n;
	}
	if(n == elders.Num())
		achievements[56] = EAchievementType::WaitActivate;
}

void FAchievement::CheckGiftAchievement() {
	if (giftTimes == 100)
		return;

	++giftTimes;
	TArray<int32> nums = { 1, 10, 50, 100 };
	CheckAchievement(nums, giftTimes, 57);
}

void FAchievement::CheckAlienateAchievement() {
	if (alienateTimes == 50)
		return;

	++alienateTimes;
	TArray<int32> nums = { 1, 10, 50 };
	CheckAchievement(nums, alienateTimes, 61);
}

void FAchievement::CheckExploreAchievement() {
	if (exploreTimes == 50)
		return;

	++exploreTimes;
	TArray<int32> nums = { 1, 10, 50 };
	CheckAchievement(nums, exploreTimes, 64);
}

void FAchievement::CheckEliminateAchievement() {
	if (eliminateTimes == 80)
		return;

	++eliminateTimes;
	TArray<int32> nums = { 1, 25, 80 };
	CheckAchievement(nums, eliminateTimes, 68);
}

void FAchievement::CheckFacilityAchievement(TArray<FFacility>& facilities) {
	TArray<int32> ids = { 0, 3, 8, 9 };
	int32 n = 0;
	for (auto& i : ids)
		if (facilities[i].IsLevelMax())
			++n;

	if(n == ids.Num())
		achievements[67] = EAchievementType::WaitActivate;
}

void FAchievement::CheckAchievement(TArray<int32>& nums, const int32& num, int32 index) {
	int32 i = 0; // 符合的索引值
	if (nums.Find(num, i)) {
		if (achievements[i + index] == EAchievementType::NoActivate)
			achievements[i + index] = EAchievementType::WaitActivate;
	}
}
