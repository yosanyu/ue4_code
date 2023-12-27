// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleBody.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UHandleBody : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	// 加入器官
	static void AddOrgan(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 選擇器官種類
	static void SwitchType(USect* sect, FOrgan temp);

	UFUNCTION(BlueprintCallable)
	static bool CanAddOrgan(USect* sect, const FOrgan& temp);

	UFUNCTION(BlueprintCallable)
	static void SellOrgan(USect* sect, int32 index, bool isInDis, EOrganType type);

	UFUNCTION(BlueprintCallable)
	// 有機械器官嗎
	static bool HasOrgan(const FOrgan& organ);

	UFUNCTION(BlueprintCallable)
	// 獲取器官詞綴
	static TArray<FEquipAffix> GetAffix(const FOrgan& organ);

	UFUNCTION(BlueprintCallable)
	// 獲取器官
	static FOrgan GetOrgan(const FBody& body, EOrganType type);

	UFUNCTION(BlueprintCallable)
	static int32 GetHealth(FBody body);

	UFUNCTION(BlueprintCallable)
	static int32 GetDamage(FBody body);

	UFUNCTION(BlueprintCallable)
	static int32 GetDefense(FBody body);

	UFUNCTION(BlueprintCallable)
	static void SortOrgan(USect* sect, EOrganType type);

	UFUNCTION(BlueprintCallable)
	// 從弟子身上取出
	static void Remove(USect* sect, int32 index, EOrganType type);

	UFUNCTION(BlueprintCallable)
	static int32 GetSingleNum(USect* sect, EOrganType type);

	//UFUNCTION(BlueprintCallable)
	static int32 GetNums(USect* sect, EOrganType type);

	UFUNCTION(BlueprintCallable)
	static FText GetSingleText(USect* sect, EOrganType type);

	UFUNCTION(BlueprintCallable)
	static int32 GetPrice(const FOrgan& organ);

	UFUNCTION(BlueprintCallable)
	static int32 GetMainValue(const FOrgan& organ);

	UFUNCTION(BlueprintCallable)
	static void SellSeveral(USect* sect, const TArray<int32>& indexs, EOrganType type);

};

FString GetOrganPath(EOrganType type);

int32 GetWhichOrgan();
