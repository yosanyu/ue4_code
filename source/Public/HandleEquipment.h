// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleEquipment.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleEquipment : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	// 加入裝備
	static void AddEquipment(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 可以打造裝備嗎?
	static bool CanMakeEquipment(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 打造裝備
	static EEquipmentType MakeEquipment(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 加入單一裝備
	static void AddSingleEquipment(USect* sect, FEquipment equipment);

	UFUNCTION(BlueprintCallable)
	// 裝備欄有空位嗎
	static bool CanAddEquipment(USect* sect, EEquipmentType type);
	
	UFUNCTION(BlueprintCallable)
	// 排序
	static void Sort(USect* sect, int32 mode);

	UFUNCTION(BlueprintCallable)
	static bool HasEquipment(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static void SellEquipment(USect* sect, int32 index, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	static FText GetName(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static int32 GetHealth(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static int32 GetDamage(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static int32 GetDefense(FEquipment e);

	UFUNCTION(BlueprintCallable)
	static bool CanEnhance(USect* sect, FEquipment e);

	UFUNCTION(BlueprintCallable)
	static bool Enhance(USect* sect, int32 index, int32 which, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	static void AutoEnhance(USect* sect, int32 index, int32 which, FEquipment e);

	UFUNCTION(BlueprintCallable)
	static int32 GetSingleEquipmentNum(USect* sect, EEquipmentType type);

	// 可以攻擊兩次嗎
	static bool CanAttackTwice(const TArray<FEquipment>& e);

	// 防禦可以提升100%嗎
	static bool CanDefenseRise(const TArray<FEquipment>& e);

	// 攻擊可以提升100%嗎
	static bool CanAttackRise(const TArray<FEquipment>& e);

	// 必定爆擊嗎
	static bool IsMustCS(const TArray<FEquipment>& e);

	UFUNCTION(BlueprintCallable)
	// 獲取詞綴效果訊息
	static FText FormatAffix(const FEquipAffix& affix);
};
