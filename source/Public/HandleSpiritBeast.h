// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleSpiritBeast.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleSpiritBeast : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void AddSpiritBeast(USect* sect);

	static FSpiritBeast CreateSB();

	UFUNCTION(BlueprintCallable)
	static void Sort(USect* sect);

	UFUNCTION(BlueprintCallable)
	static FPassiveSkill GetPassive(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static uint8 GetBlood(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static uint8 GetGrowth(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static int32 GetAge(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static int32 GetHealth(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static int32 GetAttack(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static int32 GetDefense(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static bool HasBloodPill(USect* sect);

	UFUNCTION(BlueprintCallable)
	static int32 GetBloodPillNum(USect* sect);

	UFUNCTION(BlueprintCallable)
	static bool IsDiamond(FSpiritBeast sb);

	UFUNCTION(BlueprintCallable)
	static bool RiseBlood(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static void Sell(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static void SellSeveral(USect* sect, const TArray<int32>& indexs);
};
