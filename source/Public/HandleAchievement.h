// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleAchievement.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleAchievement : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	// 獲取已達成成就的索引值
	static TArray<int32> GetAchievementIndex(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 解鎖成就後改變狀態
	static void ActivateAchievement(USect* sect, int32 id);
};

class TreasureAchievement {
public:
	// 可以完成獨門秘術成就?
	static bool CanActiveSecretMethod(int32 id, int32& num);

	// 可以完成奇特寶石成就?
	static bool CanActiveGem(int32 id, int32& num);
};
