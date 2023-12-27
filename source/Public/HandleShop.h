// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleShop.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleShop : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	// 獲取裝備價格
	static int32 GetEquipmentPrice(FEquipment equipment);

	UFUNCTION(BlueprintCallable)
	// 獲取靈獸價格
	static int32 GetSpiritBeastPrice(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	// 靈石夠買裝備嗎
	static bool CanBuyEquipment(USect* sect, FEquipment equipment);

	UFUNCTION(BlueprintCallable)
	// 裝備欄有位置放嗎
	static bool CanAddEquipment(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 買裝備
	static void BuyEquipment(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 可以買功法嗎
	static bool CanBuyLaw(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static void BuyLaw(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static bool CanBuySpiritBeast(USect* sect, FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static bool CanAddSpiritBeast(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void BuySpiritBeast(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static bool CanBuyMedicine(USect* sect, int32 buy);

	// 最大花費靈石
	UFUNCTION(BlueprintCallable)
	static int GetMaxSpiritStones(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void BuyMedicine(USect* sect, int32 buy);

	//UFUNCTION(BlueprintCallable)
	//void AddGDisP(int32 value);

	UFUNCTION(BlueprintCallable)
	static int32 GetGDisP();
};


UCLASS()
class DEVELOPVER1_API UHandleSectSystem : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void UseGift(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void UseAlienate(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void UseExplore(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void UseAttack(USect* sect);

	UFUNCTION(BlueprintCallable)
	static bool CanDraw(USect* sect);

	UFUNCTION(BlueprintCallable)
	static TArray<FEquipment> DrawEquip(USect* sect);

	UFUNCTION(BlueprintCallable)
	static FBuilding DrawBuilding(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void UseUpdate(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void Question(USect* sect, int32 index, int32 choice);
};

class AnswerQuestion {
public:
	static void Question1(USect* sect, int32 choice);
	static void Question2(int32 choice);
	static void Question3(USect* sect, int32 choice);
	static void Question4(int32 choice);
	static void Question5(int32 choice);
	static void Question6(int32 choice);
};

