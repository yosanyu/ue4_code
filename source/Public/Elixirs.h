// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AllEnum.h"
#include "Elixirs.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FElixirs : public FTableRowBase {

	GENERATED_BODY()
	FElixirs();

	bool operator== (const FElixirs& other) const;

	friend uint32 GetTypeHash(const FElixirs& other);

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	FText introduction;

	UPROPERTY(BlueprintReadWrite)
	EElixirsType type;

	UPROPERTY(BlueprintReadWrite)
	int32 value;
};
