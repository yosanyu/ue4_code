// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyGameInstance.h"
#include "HandleBattle.generated.h"

/**
 * 
 */

UCLASS()
class DEVELOPVER1_API UHandleBattle : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	static int32 GetPlayerDamage(USect* sect, const TArray<UEnemySect*>& eSect);

	UFUNCTION(BlueprintCallable)
	static int32 GetPlayerHealth(USect* sect, const TArray<UEnemySect*>& eSect);

	UFUNCTION(BlueprintCallable)
	static int32 GetPlayerDefense(USect* sect,const TArray<UEnemySect*>& eSect);

	UFUNCTION(BlueprintCallable)
	static int32 GetESectDamage(UEnemySect* sect);

	UFUNCTION(BlueprintCallable)
	static int32 GetESectHealth(UEnemySect* sect);

	UFUNCTION(BlueprintCallable)
	static int32 GetESectDefense(UEnemySect* sect);

	UFUNCTION(BlueprintCallable)
	static TArray<int32> TwoDisBattle(FDisciple player, FDisciple enemy, int32 playerH, int32 enemyH);

	UFUNCTION(BlueprintCallable)
	// 門派戰
	static TArray<int32> TeamBattle(UMyGameInstance* instance, TArray<int32> h, TArray<float> p);

	UFUNCTION(BlueprintCallable)
	// 門派戰獲取剩餘血量
	static TArray<float> GetRemaining(USect* sect, UEnemySect* enemy, int32 PH, int32 EH, const TArray<UEnemySect*>& eSect);

	UFUNCTION(BlueprintCallable)
	static TArray<int32> AttackDemon(UMyGameInstance* instance, TArray<int32> h, TArray<float> p);

	UFUNCTION(BlueprintCallable)
	// 深淵入侵獲取剩餘血量
	static TArray<float> GetDRemaining(USect* sect, const FDemon& demon, int32 PH, int32 EH, const TArray<UEnemySect*>& eSect);

	UFUNCTION(BlueprintCallable)
	static int32 IsEnd(int32 PH, int32 EH);

	UFUNCTION(BlueprintCallable)
	static bool HasEnemy(UMyGameInstance* instance);

	UFUNCTION(BlueprintCallable)
	// 使用飛彈 回傳傷害
	static int32 UseMissle(USect* sect , int32 used);

	UFUNCTION(BlueprintCallable)
	// 一鍵切磋
	static void OneClickGame(UMyGameInstance* instance);
};

void SetPlayerDamage(USect* sect, int32& damage, float percent, const TArray<UEnemySect*>& eSect);

void UseTower(USect* sect, int32& damage);

void SetPlayerDefense(USect* sect, int32& defense, float percent, const TArray<UEnemySect*>& eSect);

void SetEnemySectDamage(UEnemySect* sect, int32& damage, float percent);

void SetEnemySectDefense(UEnemySect* sect, int32& defense, float percent);
