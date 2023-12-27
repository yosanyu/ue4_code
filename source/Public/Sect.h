// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disciple.h"
#include "Facility.h"
#include "SpiritBeast.h"
#include "Shop.h"
#include "TechnologyTree.h"
#include "Elder.h"
//#include "Async/AsyncWork.h"
#include "Sect.generated.h"

/**
 * 
 */

bool HasNewData(const char* path, int32 num);

template<class T>
TArray<T> GetNewData(const char* path, int32 num) {
	TArray<T> items;
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	TArray<FName> rows = pDataTable->GetRowNames();
	for (int32 i = num; i < rows.Num(); i++) {
		T* temp = pDataTable->FindRow<T>(rows[i], "");
		if (temp != NULL) {
			items.Emplace(*temp);
		}
	}
}

USTRUCT(BlueprintType)
struct FTreasure : public FTableRowBase {
	GENERATED_BODY()
	FTreasure() {};
	UPROPERTY(BlueprintReadWrite)
	int32 id;
	UPROPERTY(BlueprintReadWrite)
	FText name;
	UPROPERTY(BlueprintReadWrite)
	FText content;
	UPROPERTY(BlueprintReadWrite)
	FText effect;
	UPROPERTY(BlueprintReadWrite)
	ESectValue type;
	UPROPERTY(BlueprintReadWrite)
	int32 value;
};

USTRUCT(BlueprintType)
struct FSaveSect  {
	GENERATED_BODY()
	FSaveSect() {};

	UPROPERTY(BlueprintReadWrite)
	TArray<FDisciple> disciples;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> weapons;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> artifacts;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> hiddenWeapons;

	UPROPERTY(BlueprintReadWrite)
	TArray<FLaw> hadLaws;

	UPROPERTY(BlueprintReadWrite)
	TArray<FLaw> noGetLaws;

	UPROPERTY(BlueprintReadWrite)
	TArray<FSpiritBeast> spiritBeasts;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTreasure> hadTreasure;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTreasure> noGetTreasures;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBuilding> hadBuilding;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBuilding> noGetBuilding;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBook> hadBooks;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBook> noGetBooks;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> hands;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> foots;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> hearts;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> lungs;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> kidneys;

	UPROPERTY(BlueprintReadWrite)
	// 設施
	TArray<FFacility> facilities;

	UPROPERTY(BlueprintReadWrite)
	// 丹藥
	TMap<FElixirs, int32> elixirs;

	UPROPERTY(BlueprintReadWrite)
	// 長老
	TArray<FElder> elders;

	UPROPERTY(BlueprintReadWrite)
	// 理念組
	TArray<bool> ideas;

	UPROPERTY(BlueprintReadWrite)
	int32 spiritStone = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 medicinalMaterials = 0;

	UPROPERTY(BlueprintReadWrite)
	// 每年靈石收入
	int32 ySpiritStone = 0;
	UPROPERTY(BlueprintReadWrite)
	// 每年藥材收入
	int32 yMedicinalMaterials = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 health = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 attack = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 defense = 0;

	// 弟子修煉速度
	UPROPERTY(BlueprintReadWrite)
	int32 speed = 0;

	UPROPERTY(BlueprintReadWrite)
	// 弟子人數上限
	int32 discipleMax = 60;

	UPROPERTY(BlueprintReadWrite)
	int32 spiritBeastMax = 30;

	UPROPERTY(BlueprintReadWrite)
	// 門派等級
	int32 level = 1;

	UPROPERTY(BlueprintReadWrite)
	int32 exp = 0;

	UPROPERTY(BlueprintReadWrite)
	// 門派飛升需要吞併或滅門的數量
	int32 toMapESect = 0;

	UPROPERTY(BlueprintReadWrite)
	// 門派飛升需要消滅的惡魔數量
	int32 toMapDemon = 0;

	UPROPERTY(BlueprintReadWrite)
	// 商行
	FShop shop;

	UPROPERTY(BlueprintReadWrite)
	// 科技樹
	FTechnologyTree tree;

	UPROPERTY(BlueprintReadWrite)
	FDefenseFacility defenseFacility;

	UPROPERTY(BlueprintReadWrite)
	//
	FSectSystem sectSystem;

	UPROPERTY(BlueprintReadWrite)
	// 每年重要紀錄
	TArray<FText> logs;

	UPROPERTY(BlueprintReadWrite)
	// 機緣記錄
	TArray<FText> chanceLogs;

	UPROPERTY(BlueprintReadWrite)
	// steam成就資料記錄
	FAchievement steamAchievement;
};

UCLASS(BlueprintType)
class DEVELOPVER1_API USect : public UObject {
	GENERATED_BODY()
public:
	USect();

	// 讀入功法
	void ReadLaws();

	// 讀入寶物
	void ReadTreasures();

	// 讀入建築
	void ReadBuildings();

	// 讀入設施
	void ReadFacility();

	// 讀入丹藥
	void ReadElixirs();

	// 讀入長老
	void ReadElders();

	// 讀入書籍
	void ReadBooks();

	UFUNCTION(BlueprintCallable)
	// 添加寶物
	void AddTreasure();

	UFUNCTION(BlueprintCallable)
	// 添加書籍
	void AddBook();

	// 每年資料更新
	void Update();

	// 計算每年收入
	void AnnualIncome();

	// 更新弟子資料
	void UpdateDisciple();

	// 更新設施資料
	void UpdateFacility();

	// 更新靈獸資料
	void UpdateSpiritBeast();

	// 增加靈石 傳入增加數量並檢查是否到達上限
	void AddSpiritStone(int32 num);

	// 增加藥材 傳入增加數量並檢查是否到達上限
	void AddMedicinalMaterials(int32 num);

	// 增加門派經驗 傳入獲得的經驗
	UFUNCTION(BlueprintCallable)
	void AddExp(int32 getExp);

	// 建造奇蹟建築 並根據類型增加對應的效果 傳入奇蹟建築的索引值
	UFUNCTION(BlueprintCallable)
	void BuildBuliding(int32 index);

	// 獲取儲存資料
	UFUNCTION(BlueprintCallable)
	FSaveSect Save();

	// 讀取資料 傳入存檔結構
	void Load(FSaveSect save);

	// 獲取五位弟子的索引值以進行切磋戰
	UFUNCTION(BlueprintCallable)
	TArray<int32> GetFiveDisIndex();

	//傳入五位弟子的索引值以獲取弟子資料
	UFUNCTION(BlueprintCallable)
	TArray<FDisciple> GetFiveDis(TArray<int32> index);

	// 邀請其他門派進行探索 獲得裝備與丹藥
	UFUNCTION(BlueprintCallable)
	TArray<FText> Explore();

	// 煉製丹藥 傳入煉製數量
	UFUNCTION(BlueprintCallable)
	TMap<FElixirs, int32> MakeElixirs(int32 num);

	UPROPERTY(BlueprintReadWrite)
	// 弟子
	TArray<FDisciple> disciples;

	UPROPERTY(BlueprintReadWrite)
	// 武器
	TArray<FEquipment> weapons;

	UPROPERTY(BlueprintReadWrite)
	// 法寶
	TArray<FEquipment> artifacts;

	UPROPERTY(BlueprintReadWrite)
	// 暗器
	TArray<FEquipment> hiddenWeapons;

	UPROPERTY(BlueprintReadWrite)
	// 已擁有的功法
	TArray<FLaw> hadLaws;

	UPROPERTY(BlueprintReadWrite)
	// 未擁有的功法
	TArray<FLaw> noGetLaws;

	UPROPERTY(BlueprintReadWrite)
	TArray<FSpiritBeast> spiritBeasts;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTreasure> hadTreasure;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTreasure> noGetTreasures;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBuilding> hadBuilding;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBuilding> noGetBuilding;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBook> hadBooks;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBook> noGetBooks;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> hands;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> foots;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> hearts;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> lungs;

	UPROPERTY(BlueprintReadWrite)
	TArray<FOrgan> kidneys;

	UPROPERTY(BlueprintReadWrite)
	// 設施
	TArray<FFacility> facilities;

	UPROPERTY(BlueprintReadWrite)
	// 丹藥
	TMap<FElixirs, int32> elixirs;

	UPROPERTY(BlueprintReadWrite)
	// 長老
	TArray<FElder> elders;

	UPROPERTY(BlueprintReadWrite)
	// 理念組
	TArray<bool> ideas;

	UPROPERTY(BlueprintReadWrite)
	int32 spiritStone = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 medicinalMaterials = 0;

	UPROPERTY(BlueprintReadWrite)
	// 每年靈石收入
	int32 ySpiritStone = 0;
	UPROPERTY(BlueprintReadWrite)
	// 每年藥材收入
	int32 yMedicinalMaterials = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 health = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 attack = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 defense = 0;

	// 弟子修煉速度
	UPROPERTY(BlueprintReadWrite)
	int32 speed = 0;

	// 弟子人數上限
	int32 discipleMax = 60;

	UPROPERTY(BlueprintReadWrite)
	int32 spiritBeastMax = 30;

	UPROPERTY(BlueprintReadWrite)
	// 門派等級
	int32 level = 1;

	int32 exp = 0;

	UPROPERTY(BlueprintReadWrite)
	// 門派飛升需要吞併或滅門的數量
	int32 toMapESect = 0;

	UPROPERTY(BlueprintReadWrite)
	// 門派飛升需要消滅的惡魔數量
	int32 toMapDemon = 0;

	UPROPERTY(BlueprintReadWrite)
	// 商行
	FShop shop;

	UPROPERTY(BlueprintReadWrite)
	// 科技樹
	FTechnologyTree tree;

	UPROPERTY(BlueprintReadWrite)
	// 防禦
	FDefenseFacility defenseFacility;

	UPROPERTY(BlueprintReadWrite)
	//門派系統
	FSectSystem sectSystem;

	UPROPERTY(BlueprintReadWrite)
	// 每年重要紀錄
	TArray<FText> logs;

	UPROPERTY(BlueprintReadWrite)
	// 機緣記錄
	TArray<FText> chanceLogs;

	UPROPERTY(BlueprintReadWrite)
	// steam成就資料記錄
	FAchievement steamAchievement;
};