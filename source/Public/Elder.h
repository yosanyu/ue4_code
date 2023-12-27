// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Elder.generated.h"
/**
 *
 */

USTRUCT(BlueprintType)
struct FElder : public FTableRowBase {

	GENERATED_BODY()

	// «Øºc¤l
	FElder();

	bool CheckSkill();

	bool IsLeveNotlMax();

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText content;

	UPROPERTY(BlueprintReadWrite)
	FText skill;

	UPROPERTY(BlueprintReadWrite)
	FText effect;

	UPROPERTY(BlueprintReadWrite)
	int32 level = 1;

	UPROPERTY(BlueprintReadWrite)
	bool useSkill = false;

};
