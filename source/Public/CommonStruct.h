// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AllEnum.h"
#include "TechnologyTree.h"
#include "Elder.h"
#include "Facility.h"
#include "CommonStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FReadText : public FTableRowBase {
	GENERATED_BODY()
	
	FReadText() {};

	UPROPERTY(BlueprintReadWrite)
	FText str;
};

USTRUCT(BlueprintType)
struct FReadStr : public FTableRowBase {
	GENERATED_BODY()

	FReadStr() {};

	UPROPERTY(BlueprintReadWrite)
	FString str;
};

USTRUCT(BlueprintType)
struct FProbability : public FTableRowBase {
	GENERATED_BODY()

	FProbability() {};

	UPROPERTY(BlueprintReadWrite)
	int32 p;
};

USTRUCT(BlueprintType)
struct FCommonAttribute : public FTableRowBase {

	GENERATED_BODY()

	// 建構子
	FCommonAttribute();

	//
	UPROPERTY(BlueprintReadWrite)
	int32 id;

	// 名稱
	UPROPERTY(BlueprintReadWrite)
	FText name;

	// 攻擊力
	UPROPERTY(BlueprintReadWrite)
	int32 attack;

	// 血量
	UPROPERTY(BlueprintReadWrite)
	int32 health;

	// 防禦
	UPROPERTY(BlueprintReadWrite)
	int32 defense;
};

USTRUCT(BlueprintType)
struct FStarSoul : public FTableRowBase {
	GENERATED_BODY()

	FStarSoul();

	UPROPERTY(BlueprintReadWrite)
	int32 id;

	UPROPERTY(BlueprintReadWrite)
	FText name;

	UPROPERTY(BlueprintReadWrite)
	int32 value;

	UPROPERTY(BlueprintReadWrite)
	EAffix type;
};

// 儲存各個變數
USTRUCT(BlueprintType)
struct FSettingSave {
	GENERATED_BODY()

	FSettingSave() {};

	UPROPERTY(BlueprintReadWrite)
	int32 year;
	UPROPERTY(BlueprintReadWrite)
	float gSectBuff;
	UPROPERTY(BlueprintReadWrite)
	float gSectHBuff;
	UPROPERTY(BlueprintReadWrite)
	float gSectABuff;
	UPROPERTY(BlueprintReadWrite)
	float gSectDBuff;
	UPROPERTY(BlueprintReadWrite)
	float gSBBuff = 0.0;
	UPROPERTY(BlueprintReadWrite)
	float gTechCost = 0.0;
	UPROPERTY(BlueprintReadWrite)
	float gYSpiritStoneMin = 0.0;
	UPROPERTY(BlueprintReadWrite)
	float gYSpiritStoneMax = 0.0;
	UPROPERTY(BlueprintReadWrite)
	float gYSpiritStonePer = 0.0;
	UPROPERTY(BlueprintReadWrite)
	float gIgnoreDefense = 0.0;
	UPROPERTY(BlueprintReadWrite)
	float gReduceDamage = 0.0;
	UPROPERTY(BlueprintReadWrite)
	int32 gMapLevel = 0; // 地圖等級
	UPROPERTY(BlueprintReadWrite)
	int32 gDisDeath = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 gDisHealth = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 gDisAttack = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 gDisDefense = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 gDisP = 0; // 弟子獲取機率加成
	UPROPERTY(BlueprintReadWrite)
	int32 gEquipP = 0; // 裝備獲取機率加成
	UPROPERTY(BlueprintReadWrite)
	int32 gSexEvent = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 gExploreEvent = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 gFriendly = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 gLanguage = 0;
};

USTRUCT(BlueprintType)
struct FAchievement {
	GENERATED_BODY()

	FAchievement();

	UPROPERTY(BlueprintReadWrite)
	// 所有成就狀態
	TArray<EAchievementType> achievements;

	UPROPERTY(BlueprintReadWrite)
	// 已建造的奇跡建築數量
	int32 buildingNum;

	UPROPERTY(BlueprintReadWrite)
	// 已招收的弟子數量
	int32 disNum;

	UPROPERTY(BlueprintReadWrite)
	// 已招收的紀元之子弟子數量
	int32 sonOfEraNum;

	UPROPERTY(BlueprintReadWrite)
	// 已驅逐的弟子數量
	int32 expelNum;

	UPROPERTY(BlueprintReadWrite)
	// 已煉製的丹藥數量
	int32 pillsNum;

	UPROPERTY(BlueprintReadWrite)
	// 已獲得的名字帶有秘術的寶物
	int32 secretMethodNum;

	UPROPERTY(BlueprintReadWrite)
	// 已獲得的名字帶有寶石的寶物
	int32 gemNum;

	UPROPERTY(BlueprintReadWrite)
	// 已獲得的仙級裝備數量
	int32 equipmentNum;

	UPROPERTY(BlueprintReadWrite)
	// 已使用的抽獎次數
	int32 drawTimes;

	UPROPERTY(BlueprintReadWrite)
	// 已使用的送禮次數
	int32 giftTimes;

	UPROPERTY(BlueprintReadWrite)
	// 已使用的離間次數
	int32 alienateTimes;

	UPROPERTY(BlueprintReadWrite)
	// 已使用的探索秘境次數
	int32 exploreTimes;

	UPROPERTY(BlueprintReadWrite)
	// 吞併或滅門成功的次數
	int32 eliminateTimes;

	// 檢查能否獲得寶物的成就
	void ChcekTreasureAchievement(int32 num);

	// 檢查能否獲得特定寶物的成就
	void SpecificTreasureAchievement(int32 id);

	// 檢查能否獲得擊敗惡魔的成就
	void ChcekDemonAchievement(int32 num);

	// 檢查能否獲得奇跡建築圖紙的成就
	void ChcekBlueprintAchievement(int32 num);

	// 檢查能否獲得建造奇跡建築的成就
	void ChcekBuildingAchievement();

	// 開局後重設弟子數量與裝備數量 避免開局影響成就
	void ResetData();

	// 檢查能否獲得招收弟子的成就
	void ChcekDiscipleAchievement(const EDiscipleRarityType& type);

	// 檢查能否獲得驅逐弟子的成就
	void CheckExpelDiscipleAchievement();

	// 檢查能否獲得煉製丹藥的成就
	void CheckPillsAchievement();

	// 檢查能否獲得仙級裝備的成就
	void CheckEquipmentAchievement();

	// 檢查能否獲得抽獎次數的成就
	void CheckDrawAchievement();

	// 檢查能否獲得科技分支滿級的成就
	void CheckTechnologyAchievement(const TArray<FTechnology>& branch, int32 mode);

	// 檢查能否獲得重返巔峰成就
	void CheckElderAchievement(TArray<FElder>& elders);

	// 檢查能否獲得送禮次數的成就
	void CheckGiftAchievement();

	// 檢查能否獲得離間次數的成就
	void CheckAlienateAchievement();

	// 檢查能否獲得探索秘境次數的成就
	void CheckExploreAchievement();

	// 檢查能否獲得吞併或滅門次數的成就
	void CheckEliminateAchievement();

	// 檢查能否獲得更多收入的成就
	void CheckFacilityAchievement(TArray<FFacility>& facilities);

	// 檢查能否獲得成就 傳入符合的數量陣列 判斷的數量 對應成就的索引值
	void CheckAchievement(TArray<int32>& nums, const int32& num, int32 index);
};