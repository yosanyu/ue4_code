// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Equipment.h"
#include "Body.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FOrgan : public FTableRowBase {
	GENERATED_BODY()

	FOrgan();

	void Create(EOrganType oType);

	int32 GetHealth();

	int32 GetDamage();

	int32 GetDefense();

	int32 GetValue(EAffix affixType);

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	int32 value;

	UPROPERTY(BlueprintReadWrite)
	int32 price;

	UPROPERTY(BlueprintReadWrite)
	int32 newValue;
	UPROPERTY(BlueprintReadWrite)
	int32 sellPrice;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipAffix> affix;

	UPROPERTY(BlueprintReadWrite)
	EOrganType type;
};
USTRUCT(BlueprintType)
struct FBody {
	GENERATED_BODY()

	FBody();

	int32 GetHealth();
	int32 GetDamage();
	int32 GetDefense();

	UPROPERTY(BlueprintReadWrite)
	FOrgan hand;
	UPROPERTY(BlueprintReadWrite)
	FOrgan foot;
	UPROPERTY(BlueprintReadWrite)
	FOrgan heart;
	UPROPERTY(BlueprintReadWrite)
	FOrgan lung;
	UPROPERTY(BlueprintReadWrite)
	FOrgan kidney;

};
