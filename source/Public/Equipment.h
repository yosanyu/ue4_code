// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonStruct.h"
#include "AllEnum.h"
#include "Constant.h"
#include "Equipment.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FEquipAffix {

	GENERATED_BODY()

	FEquipAffix();

	void Create();

	void CreateUnique(EItemRarityType rarity);

	void OrganAffix();

	void IsHealth();

	void IsAttack();

	void IsDefense();

	void IsH5();

	void IsA5();

	void IsD5();

	void IsHP();

	void IsAP();

	void IsDP();

	void IsCP();

	void IsCS();

	UPROPERTY(BlueprintReadWrite)
	EAffix affix;

	UPROPERTY(BlueprintReadWrite)
	int32 value;

	UPROPERTY(BlueprintReadWrite)
	float buff;
};

USTRUCT(BlueprintType)
struct FEquipment {

	GENERATED_BODY()

	FEquipment();

	void Create();

	void Create(EEquipmentType eType, EItemRarityType r, int32 eLevel);

	void CreateByRarity(EItemRarityType r);

	int32 GetHealth();

	int32 GetAttack();

	int32 GetDefense();

	int32 GetH5();

	int32 GetA5();

	int32 GetD5();

	float GetHP();

	float GetAP();

	float GetDP();

	int32 GetCP();

	float GetCS();

	int32 GetValue(EAffix buffType);

	float GetBuff(EAffix buffType);

	//決定裝備種類
	void DicideType();

	// 決定稀有度
	void DecideRarity();

	// 決定價錢
	void DicidePrice();

	// 讀表
	void ReadTable();

	// 決定詞綴
	void DecideAffix();

	// 強化滿等了嗎
	bool IsMaxLevel();

	// 強化
	bool LevelUp(int32& spiritStone);

	UPROPERTY(BlueprintReadWrite)
	// 裝備屬性
	FCommonAttribute attribute;

	UPROPERTY(BlueprintReadWrite)
	// 裝備種類
	EEquipmentType type;

	UPROPERTY(BlueprintReadWrite)
	// 裝備稀有度
	EItemRarityType rarity;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipAffix> affix;

	UPROPERTY(BlueprintReadWrite)
	int32 enhanceLevel = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 price = 0;
};

