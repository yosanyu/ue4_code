// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AllEnum.h"
#include "Facility.generated.h"
/**
 * 
 */
// 設施
USTRUCT(BlueprintType)
struct FFacility : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FFacility();

	// 獲取升級花費
	int32 GetLevelUpCost();

	bool IsLevelMax();

	void LevelUp();

	void Update();

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText introduction;

	UPROPERTY(BlueprintReadWrite)
	FText effect;

	UPROPERTY(BlueprintReadWrite)
	int32 value;

	UPROPERTY(BlueprintReadWrite)
	int32 level;

	UPROPERTY(BlueprintReadWrite)
	bool isOpen;

	UPROPERTY(BlueprintReadWrite)
	bool hasLevelUp = false;
};

// 防禦塔
USTRUCT(BlueprintType)
struct FTower : public FTableRowBase {

	GENERATED_BODY()

	FTower() {};

	int32 GetDamage();

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText effect;

	UPROPERTY(BlueprintReadWrite)
	int32 level;

	UPROPERTY(BlueprintReadWrite)
	int32 attack;

	UPROPERTY(BlueprintReadWrite)
	int32 price;
};

// 防禦
USTRUCT(BlueprintType)
struct FDefenseFacility {

	GENERATED_BODY()

	FDefenseFacility();

	void MakeMissle();

	UPROPERTY(BlueprintReadWrite)
	int32 missleNum;

	UPROPERTY(BlueprintReadWrite)
	int32 missleProduction;

	UPROPERTY(BlueprintReadWrite)
	int32 missleAttack;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTower> towers;

};

// 書籍
USTRUCT(BlueprintType)
struct FBook : public FTableRowBase {

	GENERATED_BODY()

	FBook() {};

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText content;

	UPROPERTY(BlueprintReadWrite)
	FText effect;

	UPROPERTY(BlueprintReadWrite)
	EBookType type;

	UPROPERTY(BlueprintReadWrite)
	int32 value;
};