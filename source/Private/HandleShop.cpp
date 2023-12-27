// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleShop.h"
#include "HandleEquipment.h"

int32 UHandleShop::GetEquipmentPrice(FEquipment equipment) {
	return int32(equipment.price * 1.2);
}

int32 UHandleShop::GetSpiritBeastPrice(FSpiritBeast sb) {
	return int32(sb.price * 1.2);
}

bool UHandleShop::CanBuyEquipment(USect* sect, FEquipment equipment) {
	if (sect->spiritStone >= GetEquipmentPrice(equipment))
		return true;
	else
		return false;
}

bool UHandleShop::CanAddEquipment(USect* sect, int32 index) {
	FEquipment temp = sect->shop.equips[index];
	bool canAdd = UHandleEquipment::CanAddEquipment(sect, temp.type);
	return canAdd;
}

void UHandleShop::BuyEquipment(USect* sect, int32 index) {
	FEquipment temp = sect->shop.equips[index];
	UHandleEquipment::AddSingleEquipment(sect, temp);
	sect->spiritStone = sect->spiritStone - GetEquipmentPrice(temp);
	sect->shop.equips[index].attribute.id = 0;
	if (temp.rarity == EItemRarityType::Immortal)
		sect->steamAchievement.CheckEquipmentAchievement();
}

bool UHandleShop::CanBuyLaw(USect* sect, int32 index) {
	if (sect->spiritStone >= sect->shop.laws[index].price)
		return true;
	else
		return false;
}

void UHandleShop::BuyLaw(USect* sect, int32 index) {
	FLaw temp = sect->shop.laws[index];
	sect->hadLaws.Emplace(temp);
	sect->spiritStone -= temp.price;
	sect->shop.laws[index].id = 0;
	for (int32 i = 0; i < sect->noGetLaws.Num(); i++) {
		if (temp.id == sect->noGetLaws[i].id) {
			sect->noGetLaws.RemoveAt(i);
			break;
		}
	}
}

bool UHandleShop::CanBuySpiritBeast(USect* sect, FSpiritBeast sb) {
	if (sect->spiritStone >= GetSpiritBeastPrice(sb))
		return true;
	else
		return false;
}

bool UHandleShop::CanAddSpiritBeast(USect* sect) {
	return sect->spiritBeasts.Num() < sect->spiritBeastMax ? true : false;
}

void UHandleShop::BuySpiritBeast(USect* sect, int32 index) {
	FSpiritBeast temp = sect->shop.spiritBeasts[index];
	sect->spiritBeasts.Emplace(temp);
	sect->spiritStone -= GetSpiritBeastPrice(temp);
	sect->shop.spiritBeasts[index].id = 0;
}

bool UHandleShop::CanBuyMedicine(USect* sect, int32 buy) {
	bool condition1 = sect->spiritStone >= buy;
	bool condition2 = (sect->medicinalMaterials + buy * 5) < gCostMax;
	if (condition1 && condition2)
		return true;
	return false;
}

int UHandleShop::GetMaxSpiritStones(USect* sect) {
	int32 min1 = (gCostMax - sect->medicinalMaterials) / 5;
	int32 min2 = sect->spiritStone;
	return FMath::Min(min1, min2);
}

void UHandleShop::BuyMedicine(USect* sect, int32 buy) {
	sect->spiritStone -= buy;
	sect->medicinalMaterials += buy * 5;
}
/*
void UHandleShop::AddGDisP(int32 value) {
	gDisP += value;
}
*/

int32 UHandleShop::GetGDisP() {
	return gDisP;
}

void UHandleSectSystem::UseGift(USect* sect) {
	FSectSystem& temp = sect->sectSystem;
	++temp.giftTimes;
	if (temp.giftTimes >= 10) {
		temp.giftTimes = 0;
		++temp.lottery;
	}
}

void UHandleSectSystem::UseAlienate(USect* sect) {
	FSectSystem& temp = sect->sectSystem;
	++temp.alienateTimes;
	if (temp.alienateTimes >= 3) {
		temp.alienateTimes = 0;
		++temp.lottery;
	}
}

void UHandleSectSystem::UseExplore(USect* sect) {
	FSectSystem& temp = sect->sectSystem;
	++temp.exploreTimes;
	if (temp.exploreTimes >= 2) {
		temp.exploreTimes = 0;
		++temp.lottery;
	}
}

void UHandleSectSystem::UseAttack(USect* sect) {
	FSectSystem& temp = sect->sectSystem;
	++temp.attackTimes;
	if (temp.attackTimes >= 4) {
		temp.attackTimes = 0;
		++temp.lottery;
	}
}

bool UHandleSectSystem::CanDraw(USect* sect) {
	return sect->sectSystem.lottery > 0;
}

TArray<FEquipment> UHandleSectSystem::DrawEquip(USect* sect) {
	--sect->sectSystem.lottery;
	TArray<FEquipment> equips;
	for (int32 i = 0; i < 3; i++) {
		FEquipment temp;
		temp.Create();
		if (UHandleEquipment::CanAddEquipment(sect, temp.type))
			UHandleEquipment::AddSingleEquipment(sect, temp);
		else
			sect->AddSpiritStone(temp.price);

		equips.Emplace(temp);
		if (temp.rarity == EItemRarityType::Immortal)
			sect->steamAchievement.CheckEquipmentAchievement();
	}
	sect->steamAchievement.CheckDrawAchievement();
	return equips;
}

FBuilding UHandleSectSystem::DrawBuilding(USect* sect) {
	if (sect->noGetBuilding.Num() > 0) { // 仍有可獲得的建築圖紙
		--sect->sectSystem.lottery;
		int32 which = FMath::RandRange(0, sect->noGetBuilding.Num() - 1);
		FBuilding temp = sect->noGetBuilding[which];
		sect->hadBuilding.Emplace(temp);
		sect->noGetBuilding.RemoveAt(which);
		int32 num = sect->hadBuilding.Num();
		sect->steamAchievement.ChcekBlueprintAchievement(num);
		sect->steamAchievement.CheckDrawAchievement();
		return temp;
	}
	return FBuilding();
}

void UHandleSectSystem::UseUpdate(USect* sect) {
	sect->spiritStone -= 500;
	--sect->shop.updateTimes;
	sect->shop.UpdateEquipments();
}

void UHandleSectSystem::Question(USect* sect, int32 index, int32 choice) {
	switch (index)
	{
	case 0:
		AnswerQuestion::Question1(sect, choice);
		break;
	case 1:
		AnswerQuestion::Question2(choice);
		break;
	case 2:
		AnswerQuestion::Question3(sect, choice);
		break;
	case 3:
		AnswerQuestion::Question4(choice);
		break;
	case 4:
		AnswerQuestion::Question5(choice);
		break;
	case 5:
		AnswerQuestion::Question6(choice);
		break;
	default:
		break;
	}
}

void AnswerQuestion::Question1(USect* sect, int32 choice) {
	switch (choice)
	{
	case 0:
		gDisP = 1;
		break;
	case 1:
		gEquipP = 1;
		break;
	case 2:
		sect->ySpiritStone += 10000;
		break;
	case 3:
		break;
	default:
		break;
	}
}

void AnswerQuestion::Question2(int32 choice) {
	switch (choice)
	{
	case 0:
		gSectHBuff += 0.03;
		break;
	case 1:
		gSectABuff += 0.03;
		break;
	case 2:
		gSectDBuff += 0.03;
		break;
	case 3:
		gSectHBuff += 0.01;
		gSectABuff += 0.01;
		gSectDBuff += 0.01;
		break;
	default:
		break;
	}
}

void AnswerQuestion::Question3(USect* sect, int32 choice) {
	switch (choice)
	{
	case 0:
		sect->discipleMax += 5;
		break;
	case 1:
		gSectBuff += 0.025;
		break;
	case 2:
		sect->discipleMax += 3;
		gSectBuff += 0.01;
		break;
	case 3:
		break;
	default:
		break;
	}
}

void AnswerQuestion::Question4(int32 choice) {
	switch (choice)
	{
	case 0:
		gYSpiritStoneMin -= 0.08;
		gYSpiritStoneMax += 0.08;
		break;
	case 1:
		gYSpiritStoneMin -= 0.25;
		gYSpiritStoneMax += 0.25;
		break;
	case 2:
		gYSpiritStonePer += 0.03;
		break;
	case 3:
		break;
	default:
		break;
	}
}

void AnswerQuestion::Question5(int32 choice) {
	switch (choice)
	{
	case 0:
		gSBBuff -= 0.05;
		break;
	case 1:
		gSBBuff += 0.05;
		break;
	case 2:
		gSBBuff += 0.1;
		break;
	case 3:
		gSBBuff -= 0.1;
		break;
	default:
		break;
	}
}

void AnswerQuestion::Question6(int32 choice) {
	switch (choice)
	{
	case 0:
		gSexEvent += 2;
		break;
	case 1:
		gTechCost += 0.12;
		break;
	case 2:
		gExploreEvent += 2;
		break;
	case 3:
		gYSpiritStonePer += 0.03;
		break;
	default:
		break;
	}
}
