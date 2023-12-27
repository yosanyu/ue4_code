// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleFacility.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleFacility : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	// 設施開放了嗎
	static bool IsOpen(FFacility facility);

	UFUNCTION(BlueprintCallable)
	// 設施這年已經升級了嗎
	static bool HasLevelUp(FFacility facility);

	UFUNCTION(BlueprintCallable)
	// 獲取升級花費
	static int32 GetLevelUpCost(FFacility facility);

	UFUNCTION(BlueprintCallable)
	// 設施可以升級嗎
	static bool CanLevelUp(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 設施升級
	static void LevelUp(USect* sect, int32 index);
	
	UFUNCTION(BlueprintCallable)
	// 可以煉製幾顆丹藥
	static int32 HowManyCanMake(USect* sect, FFacility facility);

	UFUNCTION(BlueprintCallable)
	// 獲取全屬性加成%
	static float GetPercent();

	UFUNCTION(BlueprintCallable)
	// 獲取弟子死亡氣血加成
	static int32 GetFHealth();

	UFUNCTION(BlueprintCallable)
	// 獲取弟子死亡攻擊加成
	static int32 GetFAttack();

	UFUNCTION(BlueprintCallable)
	// 獲取弟子死亡防禦加成
	static int32 GetFDefense();

	UFUNCTION(BlueprintCallable)
	static FText FormatEffect(const FFacility& facility, int32 index);

	UFUNCTION(BlueprintCallable)
	// 獲取弟子死亡人數
	static int32 GetDisDeath();

	UFUNCTION(BlueprintCallable)
	// 塔可以升級嗎
	static bool CanTowerLevelUp(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 塔升級
	static void TowerLevelUp(USect* sect, int32 index);
};

class DEVELOPVER1_API UFacilityMessage {

public:
	static FText LevelUp(USect* sect, const FFacility& facility);
};

UCLASS()
class DEVELOPVER1_API UHandleBook : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	// 可以買書嗎?
	static bool CanBuyBook(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 買書
	static void BuyBook(USect* sect);
};