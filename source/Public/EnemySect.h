// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disciple.h"
#include "Sect.h"
#include "EnemySect.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FDemon {
	GENERATED_BODY()
	FDemon() {};

	void Create();

	UPROPERTY(BlueprintReadWrite)
	FText name;
	UPROPERTY(BlueprintReadWrite)
	int32 health;
	UPROPERTY(BlueprintReadWrite)
	int32 attack;
	UPROPERTY(BlueprintReadWrite)
	int32 defense;

};

USTRUCT(BlueprintType)
struct FSaveESect {
	GENERATED_BODY()
	FSaveESect() {};
	UPROPERTY(BlueprintReadWrite)
	FText name;
	UPROPERTY(BlueprintReadWrite)
	int32 sectLevel = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 health;
	UPROPERTY(BlueprintReadWrite)
	int32 attack;
	UPROPERTY(BlueprintReadWrite)
	int32 defense;
	UPROPERTY(BlueprintReadWrite)
	TArray<FDisciple> disciples;
	UPROPERTY(BlueprintReadWrite)
	int32 friendly = 100;
	UPROPERTY(BlueprintReadWrite)
	// 可以送禮嗎
	bool canGiveGift = true;
	UPROPERTY(BlueprintReadWrite)
	// 可以使用離間嗎
	bool canUseAlienate = true;
	UPROPERTY(BlueprintReadWrite)
	// 可以邀請去探索秘境嗎
	bool canUseExplore = true;
	UPROPERTY(BlueprintReadWrite)
	// 可以進行切磋戰嗎
	bool canCommunicate = true;
	UPROPERTY(BlueprintReadWrite)
	// 被吞併了嗎
	bool hadAnnexed = false;
	UPROPERTY(BlueprintReadWrite)
	// 結盟了嗎
	bool allianced = false;
};

UCLASS(BlueprintType)
class DEVELOPVER1_API UEnemySect : public UObject {
	GENERATED_BODY()

public:
	UEnemySect();

	// 初始化
	void Create();

	// 更新資料
	void Update();

	UFUNCTION(BlueprintCallable)
	void AddFriendly(int32 point);

	UFUNCTION(BlueprintCallable)
	FSaveESect Save();

	void Load(FSaveESect save);

	UFUNCTION(BlueprintCallable)
	// 獲取五位弟子進行切磋戰
	TArray<FDisciple> GetFiveDis();

	UFUNCTION(BlueprintCallable)
	bool CanGive(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 送禮
	bool GiveGift(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 可以使用離間嗎
	bool CanAlienate();

	UFUNCTION(BlueprintCallable)
	// 使用離間
	bool Alienate(USect* sect, int32 level);

	// 驅逐弟子
	void Expel();

	UFUNCTION(BlueprintCallable)
	// 可以邀請去探索秘境嗎
	bool CanExplore();

	UFUNCTION(BlueprintCallable)
	// 探索秘境
	bool Explore(USect* sect, int32 level);

	bool IsAnnexed();

	UFUNCTION(BlueprintCallable)
	// 可以結盟嗎?
	bool CanAlliance();

	UFUNCTION(BlueprintCallable)
	// 結盟
	void Alliance();

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	int32 sectLevel = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 health;

	UPROPERTY(BlueprintReadWrite)
	int32 attack;

	UPROPERTY(BlueprintReadWrite)
	int32 defense;

	UPROPERTY(BlueprintReadWrite)
	TArray<FDisciple> disciples;

	UPROPERTY(BlueprintReadWrite)
	int32 friendly = 0;

	UPROPERTY(BlueprintReadWrite)
	// 可以送禮嗎
	bool canGiveGift = true;

	UPROPERTY(BlueprintReadWrite)
	// 可以使用離間嗎
	bool canUseAlienate = true;

	UPROPERTY(BlueprintReadWrite)
	// 可以邀請去探索秘境嗎
	bool canUseExplore = true;

	UPROPERTY(BlueprintReadWrite)
	// 可以進行切磋戰嗎
	bool canCommunicate = true;

	UPROPERTY(BlueprintReadWrite)
	// 被吞併了嗎
	bool hadAnnexed = false;

	UPROPERTY(BlueprintReadWrite)
	// 結盟了嗎
	bool allianced = false;
};

class DEVELOPVER1_API UEnemySectMessage {

public:

	static FText GiveGift(FText& name, bool successful);

	static FText UseAlienate(FText& name, int32 num, bool successful);

	static FText UseExplore(FText& name, int32 num, bool successful);
};