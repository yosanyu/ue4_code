// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Law.h"
#include "Elixirs.h"
#include "SpiritBeast.h"
#include "Shop.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FShop {

	GENERATED_BODY()

	FShop();

	// 每年更新販售的貨物 傳入尚未獲取功法的資料
	void UpdateGood(TArray<FLaw> noGet);

	// 更新販售的裝備
	void UpdateEquipments();

	// 更新販售的功法 傳入尚未獲取功法的資料
	void UpdateLaws(TArray<FLaw>& noGet);

	// 商行販售的裝備
	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> equips;

	// 商行販售的功法
	UPROPERTY(BlueprintReadWrite)
	TArray<FLaw> laws;

	// 商行販售的靈獸
	UPROPERTY(BlueprintReadWrite)
	TArray<FSpiritBeast> spiritBeasts;

	//商行刷新次數
	UPROPERTY(BlueprintReadWrite)
	int32 updateTimes = 3;

	// 弟子招收次數 每招收40位弟子提升高資質弟子的獲得機率 最高提升4次
	UPROPERTY(BlueprintReadWrite)
	int32 disTimes = 0;
};


USTRUCT(BlueprintType)
struct FSectSystem {

	GENERATED_BODY()

	FSectSystem();

	// 對其他門派送禮的次數
	UPROPERTY(BlueprintReadWrite)
	int32 giftTimes;

	// 對其他門派離間的次數
	UPROPERTY(BlueprintReadWrite)
	int32 alienateTimes;

	// 對其他門派探索秘境的次數
	UPROPERTY(BlueprintReadWrite)
	int32 exploreTimes;

	// 對其他門派攻擊的次數
	UPROPERTY(BlueprintReadWrite)
	int32 attackTimes;

	// 可抽獎的次數
	UPROPERTY(BlueprintReadWrite)
	int32 lottery;
};

USTRUCT(BlueprintType)
struct FBuilding : public FTableRowBase {

	GENERATED_BODY()

	FBuilding();

	// 奇蹟建築的id
	UPROPERTY(BlueprintReadWrite)
	int32 id;

	// 奇蹟建築的名稱
	UPROPERTY(BlueprintReadWrite)
	FText name;

	// 奇蹟建築的效果
	UPROPERTY(BlueprintReadWrite)
	FText effect;

	// 奇蹟建築加成數值
	UPROPERTY(BlueprintReadWrite)
	int32 value;

	// 奇蹟建築的建造價格
	UPROPERTY(BlueprintReadWrite)
	int32 price;

	// 奇蹟建築是否已被建造
	UPROPERTY(BlueprintReadWrite)
	bool hasBuilded;

	// 奇蹟建築效果類型
	UPROPERTY(BlueprintReadWrite)
	ESectValue type;

};