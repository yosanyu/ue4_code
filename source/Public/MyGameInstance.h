// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sect.h"
#include "EnemySect.h"
#include "MyGameInstance.generated.h"


/**
 * 
 */

UCLASS()
class DEVELOPVER1_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	UMyGameInstance();

	UFUNCTION(BlueprintCallable)
	void Create();

	void CreateEnemy();

	UFUNCTION(BlueprintCallable)
	void LoadSect(FSaveSect save, FString name);

	UFUNCTION(BlueprintCallable)
	void LoadESect(TArray<FSaveESect> save, TArray<FString> name);

	UFUNCTION(BlueprintCallable)
	void LoadSetting(FSettingSave save);

	UFUNCTION(BlueprintCallable)
	FSettingSave SaveSetting();

	UFUNCTION(BlueprintCallable)
	void LoadDisDeath(TArray<int32> values);

	UFUNCTION(BlueprintCallable)
	void AfterYear();

	UFUNCTION(BlueprintCallable)
	int32 GetYear();

	UFUNCTION(BlueprintCallable)
	float GetSectBuff();

	UFUNCTION(BlueprintCallable)
	UEnemySect* GetEnemy(int32 index);

	UFUNCTION(BlueprintCallable)
	void DealSect(int32 winOrLose);

	void AnnexSect(int32 winOrLose);

	void EliminateSect(int32 winOrLose);

	void Defense(int32 winOrLose);

	UFUNCTION(BlueprintCallable)
	void RemoveDemon();

	UFUNCTION(BlueprintCallable)
	bool CanGoToNewMap();

	UFUNCTION(BlueprintCallable)
	void ToNewMap();

	UFUNCTION(BlueprintCallable)
	bool IsEnding();

	UFUNCTION(BlueprintCallable)
	void SetLanguage(int32 which);

	UFUNCTION(BlueprintCallable)
	int32 GetLanguage();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USect* sect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 min = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UEnemySect*> enemys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 enemyIndex = 0;

	// 0是吞併 1是滅門 2 是防禦
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 eSectMode = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FDemon> demons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 demonIndex = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// 音效聲量
	float soundVolume = 1.0;

	//背景音樂聲量
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BGMVolume = 1.0;
};