// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AllEnum.h"
#include "Law.generated.h"

/**
 * 
 */

 // 儲存功法的結構
USTRUCT(BlueprintType)
struct FLaw : public FTableRowBase {
	GENERATED_BODY()

	FLaw();

	void SetPrice();

	void LevelUp();

	bool CanLevelUp();

	int32 GetNextExp();

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	// 名稱
	FText name;

	UPROPERTY(BlueprintReadWrite)
	// 攻擊
	int32 attack;

	UPROPERTY(BlueprintReadWrite)
	// 血量
	int32 health;

	UPROPERTY(BlueprintReadWrite)
	// 防禦
	int32 defense;

	UPROPERTY(BlueprintReadWrite)
	// 物品稀有度
	EItemRarityType rarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 經驗值
	int32 exp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 修煉等級
	int32 lawLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 price = 0;
};
