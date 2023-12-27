// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleElder.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleElder : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FText FormatSkillEffect(FElder e);

	UFUNCTION(BlueprintCallable)
	static int32 GetLevel(FElder e);

	UFUNCTION(BlueprintCallable)
	static int32 GetCost(FElder e);
	
	UFUNCTION(BlueprintCallable)
	static bool IsSpiritStoneEnough(USect* sect, FElder e);

	UFUNCTION(BlueprintCallable)
	static bool CanLevelUp (FElder e);

	UFUNCTION(BlueprintCallable)
	static void LevelUp(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static void UseSkill(USect* sect);

	UFUNCTION(BlueprintCallable)
	static void ResetSkill(USect* sect);

	UFUNCTION(BlueprintCallable)
	static bool CheckSkill(FElder e);
};
