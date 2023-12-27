// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnum.generated.h"
/**
 * 
 */

// 裝備種類
UENUM(BlueprintType)
enum class EEquipmentType : uint8 {
	Weapon			= 0,	// 武器
	Artifact		= 1,	// 法寶
	HiddenWeapon	= 2,	// 暗器
};

// 道具稀有度
UENUM(BlueprintType)
enum class EItemRarityType : uint8 {
	Immortal	= 0, // 仙級		1%
	Holy		= 1, // 聖級		3%
	Sky			= 2, // 天級		5%
	Earth		= 3, // 地級		8%
	Mysterious	= 4, // 玄級		14%
	Yellow		= 5, // 黃級		24%
	Human		= 6, // 人級		45%
};

// 弟子稀有度
UENUM(BlueprintType)
enum class EDiscipleRarityType : uint8 {
	SonofEra		= 0,	// 紀元之子	1%
	Genius			= 1,	// 天驕		4%
	Extraordinary	= 2,	// 非凡		9%
	Outstanding		= 3,	// 傑出		12%
	Excellent		= 4,	// 優秀		26%
	Normal			= 5,	// 一般		48%
};


// 弟子性格
UENUM(BlueprintType)
enum class EPersonality : uint8 {
	Timid		= 0,	// 膽小懦弱
	Kindness	= 1,	// 悲天憫人
	Ferocious	= 2,	// 逞凶鬥狠
	Careful		= 3,	// 謹慎求穩
	Cruel		= 4,	// 心狠手辣
};

// 弟子出身
UENUM(BlueprintType)
enum class EBackground : uint8 {
	Civilian = 0,	// 平民之子	22%
	Noble	 = 1,	// 世家子弟	15%
	Military = 2,	// 將門之後	15%
	Merchant = 3,	// 商人之子	17%
	Royal	 = 4,	// 皇室子弟	 5%
	Outcast	 = 5,	// 門派棄徒	18%
	Rebirth	 = 6,   // 大能轉世   3%
	OWVisit	 = 7,	// 異世來客   5%
};

// 道侶容貌
UENUM(BlueprintType)
enum class EAppearance : uint8 {
	SSS = 0,	// 美若天仙 屬性 + 20% 修煉速度 + 5點 爆擊機率 +  0% 爆擊傷害 + 15% 機率   1%
	SS	= 1,	// 國色天香 屬性 + 17% 修煉速度 + 4點 爆擊機率 +  0% 爆擊傷害 + 13% 機率   3%
	S	= 2,	// 閉月羞花 屬性 + 14% 修煉速度 + 3點 爆擊機率 +  0% 爆擊傷害 + 11% 機率   5%
	A	= 3,	// 我見猶憐 屬性 + 11% 修煉速度 + 2點 爆擊機率 +  0% 爆擊傷害 +  9% 機率   8%
	B	= 4,	// 豐乳肥臀 屬性 +  8% 修煉速度 + 1點 爆擊機率 +  0% 爆擊傷害 +  7% 機率  10%
	C	= 5,	// 清純可人 屬性 +  5% 修煉速度 + 0點 爆擊機率 +  0% 爆擊傷害 +  5% 機率  13%
	D	= 6,	// 相貌清秀 屬性 ±  5% 修煉速度 + 0點 爆擊機率 +  3% 爆擊傷害 +  3% 機率  20%
	E	= 7,	// 其貌不揚 屬性 -  5% 修煉速度 + 0點 爆擊機率 +  5% 爆擊傷害 +  0% 機率  13%
	F	= 8,	// 百拙千醜 屬性 -  8% 修煉速度 + 1點 爆擊機率 +  8% 爆擊傷害 +  0% 機率  10%
	G	= 9,	// 鵠面鳩形 屬性 - 11% 修煉速度 + 1點 爆擊機率 + 11% 爆擊傷害 +  0% 機率   8%
	H	= 10,	// 支離臃腫 屬性 - 14% 修煉速度 + 1點 爆擊機率 + 14% 爆擊傷害 +  0% 機率   5%
	I	= 11,	// 臼頭深目 屬性 - 17% 修煉速度 + 1點 爆擊機率 + 17% 爆擊傷害 +  0% 機率   3%
	J	= 12,	// 奇醜無比 屬性 - 20% 修煉速度 + 1點 爆擊機率 + 20% 爆擊傷害 +  0% 機率   1%
};

// 道侶性格
UENUM(BlueprintType)
enum class EWPersonality : uint8 { 
	SSS =  0,	// 千依百順 屬性 + 15% 修煉速度 + 2點 爆擊機率 +   6% 爆擊傷害 +  5%
	SS  =  1,	// 德才兼備 屬性 + 13% 修煉速度 + 2點 爆擊機率 +   5% 爆擊傷害 +  5%
	S   =  2,	// 善解人意 屬性 + 11% 修煉速度 + 2點 爆擊機率 +   4% 爆擊傷害 +  5%
	A   =  3,	// 溫婉賢淑 屬性 +  9% 修煉速度 + 1點 爆擊機率 +   3% 爆擊傷害 +  5%
	B   =  4,	// 處事周到 屬性 +  7% 修煉速度 + 1點 爆擊機率 +   2% 爆擊傷害 +  5%
	C   =  5,	// 溫柔婉約 屬性 +  5% 修煉速度 + 1點 爆擊機率 +   1% 爆擊傷害 +  5%
	D   =  6,	// 冷若冰霜 屬性 ±  3% 修煉速度 + 0點 爆擊機率 +   0% 爆擊傷害 +  3%
	E   =  7,	// 善妒易怒 屬性 -  5% 修煉速度 + 0點 爆擊機率 +   2% 爆擊傷害 +  5%
	F   =  8,	// 蠻橫無理 屬性 -  7% 修煉速度 + 0點 爆擊機率 +   4% 爆擊傷害 +  7%
	G   =  9,	// 冷血陰狠 屬性 -  9% 修煉速度 + 0點 爆擊機率 +   6% 爆擊傷害 +  9%
	H   = 10,	// 囂張跋扈 屬性 - 11% 修煉速度 + 0點 爆擊機率 +   8% 爆擊傷害 + 11%
	I   = 11,	// 心高氣傲 屬性 - 13% 修煉速度 + 0點 爆擊機率 +  10% 爆擊傷害 + 13%
	J   = 12,	// 自命不凡 屬性 - 15% 修煉速度 + 0點 爆擊機率 +  12% 爆擊傷害 + 15%
};

// 寶物類型
UENUM(BlueprintType)
enum class ESectValue : uint8 {
	SpiritStone			= 0, // 每年增加靈石
	MedicinalMaterials	= 1, // 每年增加藥材
	Health				= 2, // 增加門派氣血
	Attack				= 3, // 增加門派傷害
	Defense				= 4, // 增加門派防禦
	Speed				= 5, // 增加修煉速度
	AttributePercent	= 6, // 增加弟子全屬%
	AllAttribute		= 7, // 增加門派全屬
	SexyEvent			= 8, // 雙修機率
};

// 裝備詞綴
UENUM(BlueprintType)
enum class EAffix : uint8 {
	Health			= 0,  // 10% 氣血 T1 1000~1500 T2 700~1000 T3 400~700 T4 50~400
	Attack			= 1,  // 10% 傷害 T1 400~600 T2 250~400 T3 100~250
	Defense			= 2,  // 10% 防禦 T1 300~400 T2 200~300 T3 100~200
	H5				= 3,  // 10% 根骨 1~100
	A5				= 4,  // 10% 攻擊 1~100
	D5				= 5,  // 10% 體魄 1~100
	HP				= 6,  // 10% 根骨% 10~25
	AP				= 7,  // 10% 攻擊% 10~25
	DP				= 8,  // 10% 體魄% 10~25
	CriticalP		= 9,  //  5% 爆擊機率 1~5%
	CriticalStrike  = 10, //  5% 爆擊傷害 1~5%
	TwiceAttack		= 11, // 每回合有10%/20%機率攻擊兩次
	DobuleDefense	= 12, // 每回合有10%/20%機率防禦*2
	DoubleAttack	= 13, // 每回合有10%/20%機率攻擊*2
	MustCriticalP	= 14, // 必定爆擊
	None			= 15,
};

// 丹藥類型
UENUM(BlueprintType)
enum class EElixirsType : uint8 {
	Health	= 0, // 提升根骨
	Attack	= 1, // 提升攻擊
	Defense = 2, // 提升體魄
	All		= 3, // 提升全屬
	Rarity	= 4, // 提升資質
};

// 靈獸天賦種類
UENUM(BlueprintType)
enum class EPassiveSkill : uint8 {
	Health  = 0,
	Attack  = 1,
	Defense = 2,
	All		= 3,
};

// 靈獸生長期
UENUM(BlueprintType)
enum class EGrowing : uint8 {
	Old		  = 0, // 老年期
	Maturity  = 1, // 成熟期
	Growth    = 2, // 成長期
	Childhood = 3, // 幼年期
};

// 靈獸血脈等級
UENUM(BlueprintType)
enum class EBlood : uint8 {
	Diamond   = 0, // 鑽石級
	Platinum  = 1, // 白金級
	Gold	  = 2, // 黃金級
	Silver	  = 3, // 白銀級
	Bronze	  = 4, // 青銅級
	BlackIron = 5, // 黑鐵級
};

// 科技類型
UENUM(BlueprintType)
enum class ETechnologyType : uint8 {
	Health				= 0, // 氣血
	Attack				= 1, // 攻擊
	Defense				= 2, // 防禦
	ALLAttribute		= 3, // 三種屬性
	SpiritStone			= 4, // 靈石
	MedicinalMaterials	= 5, // 藥材
	SSMM				= 6, // 靈石+藥材
	Facility			= 7, // 開放設施
	Disciple			= 8, // 弟子全屬性
	IgnoreDefense		= 9, // 無視防禦率
};

// 書籍類型
UENUM(BlueprintType)
enum class EBookType : uint8 {
	Health				 =  0, // 氣血
	Damage				 =  1, // 傷害
	Defense				 =  2, // 防禦
	ALLAttribute		 =  3, // 三種屬性
	SpiritStone			 =  4, // 靈石
	MedicinalMaterials	 =  5, // 藥材
	Disciple			 =  6, // 弟子全屬性
	IgnoreDefense		 =  7, // 無視防禦率
	ReduceDamage		 =  8, // 減少受到的傷害 
	Speed				 =  9, // 弟子修煉速度
	TechnologyCost		 = 10, // 科技花費
	Friendly			 = 11, // 友好度
	NoEffect			 = 12, // 沒有效果
	SpiritBeast			 = 13, // 靈獸全屬性
};

// 器官
UENUM(BlueprintType)
enum class EOrganType : uint8 {
	Hand	= 0, // 手
	Foot	= 1, // 腳
	Heart	= 2, // 心
	Lung	= 3, // 肺
	Kidney	= 4, // 腎
};

// 成就啟用狀態
UENUM(BlueprintType)
enum class EAchievementType : uint8 {
	NoActivate   =	0,
	WaitActivate =	1,
	Actived		 =	2,
};

