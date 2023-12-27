// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AllEnum.h"
#include "TechnologyTree.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTechnology : public FTableRowBase {

	GENERATED_BODY()
	FTechnology();

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText content;

	UPROPERTY(BlueprintReadWrite)
	FText effect;

	UPROPERTY(BlueprintReadWrite)
	int32 value;

	UPROPERTY(BlueprintReadWrite)
	int32 level = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 maxLevel;

	UPROPERTY(BlueprintReadWrite)
	int32 price;

	UPROPERTY(BlueprintReadWrite)
	ETechnologyType type;
};


USTRUCT(BlueprintType)
struct FTechnologyTree {
	GENERATED_BODY()

	FTechnologyTree();

	void ReadEconomic();

	void ReadFormations();

	void ReadSchools();

	UPROPERTY(BlueprintReadWrite)
	TArray<FTechnology> economic;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTechnology> formations;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTechnology> schools;

	UPROPERTY(BlueprintReadWrite)
	int32 levelupLimit;
};