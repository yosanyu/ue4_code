// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonStruct.h"
//#include "Constant.generated.h"


/**
 * 
 */

void SetYear(int32 y);

void AfterAYear();
int32 GetNowYear();

FString ReadSectMessage(int32 index);

FText FormatBattleMessage(FText sectName, int32 index);
FText FormatFailedMessage(FText sectName, int32 index, int32 loss);

 // 武器路徑表
TArray<FString> GetWeaponPath();

// 法寶路徑表
TArray<FString> GetArtifactPath();

// 暗器路徑表
TArray<FString> GetHiddenWeaponPath();

const char* GetDiscipleNamePath(int32 choice);

constexpr int32 gCostMax = 100000000;

float gSectBuff = 0.0; // 門派弟子buff

float gSectHBuff = 0.0; // 門派總氣血buff

float gSectABuff = 0.0; // 門派總傷害buff

float gSectDBuff = 0.0; // 門派總防禦buff

float gSBBuff = 0.0; // 靈獸全屬性buff

float gTechCost = 0.0; // 科技升級花費加成

float gYSpiritStoneMin = 0.0;

float gYSpiritStoneMax = 0.0;

float gYSpiritStonePer = 0.0; // 每年靈石收入加成

float gIgnoreDefense = 0.0; // 無視防禦率

float gReduceDamage = 0.0; // 減少受到的傷害

int32 gMapLevel = 0; // 地圖等級

int32 gDisDeath = 0;

int32 gDisHealth = 0;

int32 gDisAttack = 0;

int32 gDisDefense = 0;

int32 gDisP = 0; // 弟子獲取機率加成

int32 gEquipP = 0; // 裝備獲取機率加成

int32 gSexEvent = 0;

int32 gExploreEvent = 0;

int32 gFriendly = 0; // 每年增加門派友好度

int32 gLanguage = 0; // 遊戲語言 0英文 1繁中 2簡中
