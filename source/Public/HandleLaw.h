// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleLaw.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleLaw : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	// 有功法嗎
	static bool HasLaw(FLaw law);

	UFUNCTION(BlueprintCallable)
	// 排序
	static void Sort(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 獲取升至下一級的經驗
	static int32 GetNextLevelExp(FLaw law);

	UFUNCTION(BlueprintCallable)
	// 獲取氣血
	static int32 GetHealth(FLaw law);

	UFUNCTION(BlueprintCallable)
	// 獲取傷害
	static int32 GetDamage(FLaw law);

	UFUNCTION(BlueprintCallable)
	// 獲取防禦
	static int32 GetDefense(FLaw law);

	UFUNCTION(BlueprintCallable)
	// 獲取功法數量
	static FText GetLawNums(USect* sect);
};
