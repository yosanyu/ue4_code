// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleLaw.h"

bool UHandleLaw::HasLaw(FLaw law) {
	return law.id == 9999 ? false : true;
}

void UHandleLaw::Sort(USect* sect) {
	sect->hadLaws.Sort([](const FLaw& A, const FLaw& B) {
		return A.id < B.id;
	});
}

int32 UHandleLaw::GetNextLevelExp(FLaw law) {
	return law.GetNextExp() - law.exp;
}

int32 UHandleLaw::GetHealth(FLaw law) {
	return law.health * (1 + 0.1 * (law.lawLevel));
}

int32 UHandleLaw::GetDamage(FLaw law) {
	return law.attack* (1 + 0.1 * (law.lawLevel));
}

int32 UHandleLaw::GetDefense(FLaw law) {
	return law.defense * (1 + 0.1 * (law.lawLevel));
}

FText UHandleLaw::GetLawNums(USect* sect) {
	FString str = "{0}/{1}";
	TArray<FStringFormatArg> args = { 
		FStringFormatArg(sect->hadLaws.Num()),
		FStringFormatArg(sect->hadLaws.Num() + sect->noGetLaws.Num()) 
	};
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}
