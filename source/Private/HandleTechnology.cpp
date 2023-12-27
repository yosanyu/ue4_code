// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleTechnology.h"

int32 UHandleTechnology::GetLevel(FTechnology t) {
	return t.level;
}

int32 UHandleTechnology::GetLevelUpCost(FTechnology t) {
	float cost = 1.0 - gTechCost;
	return int32(t.price * cost);
}

bool UHandleTechnology::IsSpiritStoneEnough(USect* sect, FTechnology t) {
	return sect->spiritStone >= GetLevelUpCost(t);
}

bool UHandleTechnology::LevelUpTimesFull(USect* sect) {
	return sect->tree.levelupLimit == 20; // 20
}

bool UHandleTechnology::CanLevelUp(FTechnology t) {
	return t.level < t.maxLevel;
}

void UHandleTechnology::LevelUp(USect* sect, int32 index, int32 mode) {
	FTechnology technology;
	// 0是經濟 1是陣法 2是學派
	switch (mode)
	{
	case 0:
		++sect->tree.economic[index].level;
		technology = sect->tree.economic[index];
		sect->steamAchievement.CheckTechnologyAchievement(sect->tree.economic, 0);
		break;
	case 1:
		++sect->tree.formations[index].level;
		technology = sect->tree.formations[index];
		sect->steamAchievement.CheckTechnologyAchievement(sect->tree.formations, 1);
		break;
	case 2:
		++sect->tree.schools[index].level;
		technology = sect->tree.schools[index];
		sect->steamAchievement.CheckTechnologyAchievement(sect->tree.schools, 2);
		break;
	default:
		break;
	}

	sect->spiritStone -= GetLevelUpCost(technology);
	++sect->tree.levelupLimit;
	ETechnologyType type = technology.type;
	switch (type)
	{
	case ETechnologyType::Health:
		sect->health += technology.value;
		break;
	case ETechnologyType::Attack:
		sect->attack += technology.value;
		break;
	case ETechnologyType::Defense:
		sect->defense += technology.value;
		break;
	case ETechnologyType::ALLAttribute:
		sect->health += technology.value;
		sect->attack += technology.value;
		break;
	case ETechnologyType::SpiritStone:
		sect->ySpiritStone += technology.value;
		break;
	case ETechnologyType::MedicinalMaterials:
		sect->yMedicinalMaterials += technology.value;
		break;
	case ETechnologyType::SSMM:
		sect->ySpiritStone += technology.value;
		sect->yMedicinalMaterials += technology.value;
		break;
	case ETechnologyType::Facility:
		sect->facilities[index - 3].isOpen = true;
		break;
	case ETechnologyType::Disciple:
		gSectBuff += 0.002;
		break;
	case ETechnologyType::IgnoreDefense:
		gIgnoreDefense += 0.4;
		break;
	default:
		break;
	}
	if (technology.level == technology.maxLevel)
		++sect->sectSystem.lottery;
}

void UHandleTechnology::UseIdea(USect* sect, int32 index) {
	switch (index)
	{
	case 0:
		if (sect->ideas[1]) {
			gYSpiritStoneMin -= 0.15;
			gYSpiritStoneMax += 0.15;
		}
		sect->ideas[0] = true;
		sect->ideas[1] = false;
		gYSpiritStonePer += 0.05;
		break;
	case 1:
		if(sect->ideas[0])
			gYSpiritStonePer -= 0.05;
		sect->ideas[0] = false;
		sect->ideas[1] = true;
		gYSpiritStoneMin -= 0.15;
		gYSpiritStoneMax += 0.15;
		break;
	case 2:
		if (sect->ideas[3])
			gSectBuff -= 0.05;
		sect->ideas[2] = true;
		sect->ideas[3] = false;
		sect->discipleMax += 10;
		sect->spiritBeastMax += 20;
		break;
	case 3:
		if (sect->ideas[2]) {
			sect->discipleMax -= 10;
			sect->spiritBeastMax -= 20;
		}
		sect->ideas[2] = false;
		sect->ideas[3] = true;
		gSectBuff += 0.05;
		break;
	case 4:
		sect->ideas[4] = true;
		sect->ideas[5] = false;
		gFriendly += 2;
		break;
	case 5:
		if(sect->ideas[4])
			gFriendly -= 2;
		sect->ideas[4] = false;
		sect->ideas[5] = true;
		break;
	default:
		break;
	}
}

bool UHandleTechnology::CanUseEliteIdea(USect* sect) {
	if (!sect->ideas[2])
		return true;

	int32 disNum = sect->disciples.Num();
	int32 sbNum = sect->spiritBeasts.Num();
	return disNum <= sect->discipleMax - 10 && sbNum <= sect->spiritBeastMax - 20;
}

int32 UHandleTechnology::GetMinSpiritStone(USect* sect) {
	float buff = 1.0 + gYSpiritStoneMin + gYSpiritStonePer;
	return int32(sect->ySpiritStone * buff);
}

int32 UHandleTechnology::GetMaxSpiritStone(USect* sect) {
	float buff = 1.0 + gYSpiritStoneMax + gYSpiritStonePer;
	return int32(sect->ySpiritStone * buff);
}

float UHandleTechnology::GetMinSSPer() {
	return gYSpiritStoneMin;
}
