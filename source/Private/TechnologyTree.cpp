// Fill out your copyright notice in the Description page of Project Settings.


#include "TechnologyTree.h"

FTechnology::FTechnology() {

}

FTechnologyTree::FTechnologyTree() {
	ReadEconomic();
	ReadFormations();
	ReadSchools();
	levelupLimit = 0;
}

void FTechnologyTree::ReadEconomic() {
	const char* path = "DataTable'/Game/DataTable/Technology/Economic.Economic'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& row : rowNames) {
			FTechnology* data = pDataTable->FindRow<FTechnology>(row, "");
			if (data != NULL) {
				economic.Emplace(*data);
			}
		}
	}
}

void FTechnologyTree::ReadFormations() {
	const char* path = "DataTable'/Game/DataTable/Technology/Formation.Formation'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& row : rowNames) {
			FTechnology* data = pDataTable->FindRow<FTechnology>(row, "");
			if (data != NULL) {
				formations.Emplace(*data);
			}
		}
	}
}

void FTechnologyTree::ReadSchools() {
	const char* path = "DataTable'/Game/DataTable/Technology/Schools.Schools'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (auto& row : rowNames) {
			FTechnology* data = pDataTable->FindRow<FTechnology>(row, "");
			if (data != NULL) {
				schools.Emplace(*data);
			}
		}
	}
}
