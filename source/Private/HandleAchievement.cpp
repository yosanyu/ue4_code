// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleAchievement.h"
#include "Misc/Paths.h"

//void* DLLHandle = NULL;

//typedef bool(*DLLTest)(int id);
//DLLTest Test = NULL;

TArray<int32> UHandleAchievement::GetAchievementIndex(USect* sect) {
	TArray<int32> id;
	TArray<EAchievementType>& achievements = sect->steamAchievement.achievements;
	for (int32 i = 0; i < achievements.Num(); i++) {
		if (achievements[i] == EAchievementType::WaitActivate)
			id.Emplace(i);
	}
	return id;
}

void UHandleAchievement::ActivateAchievement(USect* sect, int32 id) {
	TArray<EAchievementType>& achievements = sect->steamAchievement.achievements;
	achievements[id] = EAchievementType::Actived;
}


bool TreasureAchievement::CanActiveSecretMethod(int32 id, int32& num) {
	/*
	if (DLLHandle == NULL) {
		FString filePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("DLL/"), TEXT("UE4Dll.dll"));
		if (FPaths::FileExists(*filePath)) {
			DLLHandle = FPlatformProcess::GetDllHandle(*filePath);
		}
	}
	
	if (Test == NULL) {
		FString procName = "CanActiveSecretMethod";
		Test = (DLLTest)FPlatformProcess::GetDllExport(DLLHandle, *procName);
	}
	*/
	
	if (num == 5)
		return false;

	TArray<int32> ids = { 156, 157, 158, 159, 160, 161, 162, 163, 164 };
	if (ids.Contains(id) == true)
		++num;
	/*
	if (Test(id))
		++num;
	*/
	return num == 5 ? true : false;
}

bool TreasureAchievement::CanActiveGem(int32 id, int32& num) {
	if (num == 15)
		return false;
	TArray<int32> ids = { 73 };
	for (int32 i = 75; i <= 109; i++)
		ids.Emplace(i);
	if (ids.Contains(id) == true)
		++num;

	return num == 15 ? true : false;
}
