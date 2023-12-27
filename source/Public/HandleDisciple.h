// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "HandleDisciple.generated.h"

/**
 * 
 */

FString Read(int32 index);

UCLASS()
class DEVELOPVER1_API UHandleDisciple : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	// 加入新弟子
	static void AddDisciple(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 有靈石可以招收弟子嗎?
	static bool SpiritStoneEnough(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 可以招收弟子嗎?
	static bool CanRecruitDisciple(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 招收弟子
	static void RecruitDisciple(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 招收多個弟子
	static void RecruitDisciples(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 弟子排序
	static void Sort(USect* sect);

	UFUNCTION(BlueprintCallable)
	// 驅逐多個弟子
	static void ExpelSeveral(USect* sect, const TArray<int32>& indexs);

	UFUNCTION(BlueprintCallable)
	// 驅逐弟子
	static void Expel(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	// 穿上裝備
	static void UseEquipment(USect* sect, int32 disIndex, int32 equipIndex, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	// 穿上全部裝備
	static void UseEquipments(USect* sect, int32 disIndex);

	UFUNCTION(BlueprintCallable)
	// 賣掉裝備
	static void SellEquipment(USect* sect, int32 index, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	// 卸下裝備
	static void RemoveEquipment(USect* sect, int32 disIndex, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	// 身上有裝備嗎
	static bool HasEquipment(USect* sect, int32 disIndex, EEquipmentType type);

	UFUNCTION(BlueprintCallable)
	// 弟子資質能學嗎
	static bool RarityCanLearn(const FDisciple&dis , const FLaw& law);

	UFUNCTION(BlueprintCallable)
	static bool CanUseElixirs(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	// 吃丹藥
	static void UseElixirs(USect* sect, int32 disIndex, FElixirs elixirs);

	UFUNCTION(BlueprintCallable)
	// 吃可提升資質的補天丸
	static bool UseRarityPill(USect* sect, int32 disIndex, FElixirs elixirs);

	UFUNCTION(BlueprintCallable)
	static void SortElixirs(USect* sect, int32 disIndex);

	UFUNCTION(BlueprintCallable)
	// 已經學過了嗎
	static bool CanLearnLaw(USect* sect, int32 disIndex, FLaw law);

	UFUNCTION(BlueprintCallable)
	// 學功法
	static void LearnLaw(USect* sect, int32 disIndex, FLaw law, int32 index);

	UFUNCTION(BlueprintCallable)
	// 學多個功法
	static void LearnLaws(USect* sect, int32 disIndex);

	UFUNCTION(BlueprintCallable)
	// 獲取學過的功法
	static TArray<FLaw> GetLaws(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	// 獲取修煉速度
	static int32 GetCultivateSpeed(USect* sect, FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static bool IsMarried(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static void Marry(USect* sect, int32 index, FWife wife);

	UFUNCTION(BlueprintCallable)
	static void Divorce(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static void UseOrgan(USect* sect, int32 disIndex, EOrganType type, int32 OrganIndex);

	UFUNCTION(BlueprintCallable)
	static void UseOrgans(USect* sect, int32 disIndex);

	UFUNCTION(BlueprintCallable)
	static bool HasTypeOrgan(const FDisciple& dis, EOrganType type);

	UFUNCTION(BlueprintCallable)
	static TArray<FWife> GetWifes();

	// 獲取根骨
	UFUNCTION(BlueprintCallable)
	static int32 GetH5(FDisciple dis);

	// 獲取攻擊
	UFUNCTION(BlueprintCallable)
	static int32 GetA5(FDisciple dis);

	// 獲取體魄
	UFUNCTION(BlueprintCallable)
	static int32 GetD5(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static int32 GetHealth(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static int32 GetDamage(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static int32 GetDefense(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static int32 GetCP(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static float GetCS(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	// 門派切磋後，增加弟子屬性
	static FText AfterBattle(USect* sect, int32 index);

	UFUNCTION(BlueprintCallable)
	static bool IsSonofEra(FDisciple dis);

	UFUNCTION(BlueprintCallable)
	static FText GetDiscipleNums(USect* sect);

};

class DEVELOPVER1_API UDiscipleMessage {

public:

	static FText LearnLaw(FLaw& law, int32 year);

	static FText LearnNewLaw(FLaw& law, int32 year);

	static FText LawToLimit(FLaw& law, int32 year);

	static FText LevelUp(int32 level, int32 year);

	static FText GetMarry(FText& name1, FText& name2, int32 year);

	static FText GetDivorce(FText& name1, FText& name2, int32 year);

	static FText GetAfterBattle(FDisciple& dis, TArray<int32> attribute);
};
