// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleTechnology.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleTechnology : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	// 獲取科技等級
	static int32 GetLevel(FTechnology t);

	UFUNCTION(BlueprintCallable)
	static int32 GetLevelUpCost(FTechnology t);

	UFUNCTION(BlueprintCallable)
	// 靈石足夠嗎
	static bool IsSpiritStoneEnough(USect* sect, FTechnology t);

	UFUNCTION(BlueprintCallable)
	// 今年次數用完了嗎
	static bool LevelUpTimesFull(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 可以升級嗎
	static bool CanLevelUp(FTechnology t);

	UFUNCTION(BlueprintCallable)
	// 升級
	static void LevelUp(USect* sect, int32 index, int32 mode);

	UFUNCTION(BlueprintCallable)
	// 啟用理念
	static void UseIdea(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 可以啟用菁英理念嗎
	static bool CanUseEliteIdea(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 獲得最低靈石收入
	static int32 GetMinSpiritStone(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 獲得最高靈石收入
	static int32 GetMaxSpiritStone(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 獲得最低靈石%數
	static float GetMinSSPer();
};
