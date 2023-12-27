// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleElder.h"

FText UHandleElder::FormatSkillEffect(FElder e) {
	FString str = "";
	TArray<FStringFormatArg> args =  {FStringFormatArg(20 + e.level) };
	str = str.Format(*e.effect.ToString(), args);
	return FText::FromString(*str);
}

int32 UHandleElder::GetLevel(FElder e) {
	return e.level;
}

int32 UHandleElder::GetCost(FElder e){
	return 40000;
}

bool UHandleElder::IsSpiritStoneEnough(USect* sect, FElder e) {
	return sect->spiritStone >= GetCost(e);
}

bool UHandleElder::CanLevelUp(FElder e) {
	return e.IsLeveNotlMax();
}

void UHandleElder::LevelUp(USect* sect, int32 index) {
	sect->spiritStone -= 40000;
	++sect->elders[index].level;
	sect->steamAchievement.CheckElderAchievement(sect->elders);
}

void UHandleElder::UseSkill(USect* sect) {
	for (auto& i : sect->elders) {
		if (FMath::RandRange(1, 100) <= i.level + 20) // 10
			i.useSkill = true;
	}
}

void UHandleElder::ResetSkill(USect* sect) {
	for (auto& i : sect->elders)
			i.useSkill = false;
}

bool UHandleElder::CheckSkill(FElder e) {
	return e.CheckSkill();
}
