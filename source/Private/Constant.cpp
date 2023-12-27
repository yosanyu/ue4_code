// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\Constant.h"
#include "Engine/DataTable.h"
#include "CommonStruct.h"

int32 gYears = 1;

void SetYear(int32 y) {
	gYears = y;
}

void AfterAYear() {
	if(gYears < 100000000)
		++gYears;
}

int32 GetNowYear() {
	return gYears;
}

FString ReadSectMessage(int32 index) {
	const char* path = "DataTable'/Game/DataTable/Message/SectMessage.SectMessage'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FReadText* data = pDataTable->FindRow<FReadText>(FName(*FString::FromInt(index)), "");
		if (data != NULL) {
			return data->str.ToString();
		}
	}
	return FString();
}

FText FormatBattleMessage(FText sectName, int32 index) {
	FString str = "";
	str = ReadSectMessage(index);
	TArray<FStringFormatArg> args = { FStringFormatArg(sectName.ToString()) };
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText FormatFailedMessage(FText sectName, int32 index, int32 loss) {
	FString str = "";
	str = ReadSectMessage(index);
	TArray<FStringFormatArg> args = { FStringFormatArg(sectName.ToString()), FStringFormatArg(loss) };
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

TArray<FString> GetWeaponPath() {
	TArray<FString> path = {
	"DataTable'/Game/DataTable/Equipment/Weapon/ImmortalWeapon.ImmortalWeapon'",
	"DataTable'/Game/DataTable/Equipment/Weapon/HolyWeapon.HolyWeapon'",
	"DataTable'/Game/DataTable/Equipment/Weapon/SkyWepaon.SkyWepaon'",
	"DataTable'/Game/DataTable/Equipment/Weapon/EarthWeapon.EarthWeapon'",
	"DataTable'/Game/DataTable/Equipment/Weapon/MysteriousWeapon.MysteriousWeapon'",
	"DataTable'/Game/DataTable/Equipment/Weapon/YellowWeapon.YellowWeapon'",
	"DataTable'/Game/DataTable/Equipment/Weapon/HumanWeapon.HumanWeapon'"
	};
	return path;
}

TArray<FString> GetArtifactPath() {
	TArray<FString> path = {
	"DataTable'/Game/DataTable/Equipment/Artifact/ImmortalArtifact.ImmortalArtifact'",
	"DataTable'/Game/DataTable/Equipment/Artifact/HolyArtifact.HolyArtifact'",
	"DataTable'/Game/DataTable/Equipment/Artifact/SkyArtifact.SkyArtifact'",
	"DataTable'/Game/DataTable/Equipment/Artifact/EarthArtifact.EarthArtifact'",
	"DataTable'/Game/DataTable/Equipment/Artifact/MysteriousArtifact.MysteriousArtifact'",
	"DataTable'/Game/DataTable/Equipment/Artifact/YellowArtifact.YellowArtifact'",
	"DataTable'/Game/DataTable/Equipment/Artifact/HumanArtifact.HumanArtifact'"
	};
	return path;
}


TArray<FString> GetHiddenWeaponPath() {
	TArray<FString> path = {
	"DataTable'/Game/DataTable/Equipment/HiddenWeapon/ImmortalHiddenWeapon.ImmortalHiddenWeapon'",
	"DataTable'/Game/DataTable/Equipment/HiddenWeapon/HolyHiddenWeapon.HolyHiddenWeapon'",
	"DataTable'/Game/DataTable/Equipment/HiddenWeapon/SkyHiddenWeapon.SkyHiddenWeapon'",
	"DataTable'/Game/DataTable/Equipment/HiddenWeapon/EarthHiddenWeapon.EarthHiddenWeapon'",
	"DataTable'/Game/DataTable/Equipment/HiddenWeapon/MysteriousHiddenWeapon.MysteriousHiddenWeapon'",
	"DataTable'/Game/DataTable/Equipment/HiddenWeapon/YellowHiddenWeapon.YellowHiddenWeapon'",
	"DataTable'/Game/DataTable/Equipment/HiddenWeapon/HumanHiddenWeapon.HumanHiddenWeapon'"
	};
	return path;
}

const char* GetDiscipleNamePath(int32 choice) {
	const char* path = nullptr;
	switch (choice)
	{
	case 1:
		path = "DataTable'/Game/DataTable/name/Surname.Surname'";
		break;
	case 2:
		path = "DataTable'/Game/DataTable/name/Name.Name'";
		break;
	case 3:
		path = "DataTable'/Game/DataTable/name/GName.GName'";
		break;
	default:
		break;
	}
	return path;
}
