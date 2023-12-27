// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySect.h"
#include "Constant.h"

UEnemySect::UEnemySect() {
	name = FText();
	health = 0;
	attack = 0;
	defense = 0;
}

void UEnemySect::Create() {
	name = FText();
	friendly = 20;
	for (int32 i = 0; i < 100; i++) {
		FDisciple temp;
		temp.SetEnemy();
		disciples.Emplace(temp);
	}
	//hadAnnexed = true;
}

void UEnemySect::Update() {
	canGiveGift = true;
	canUseAlienate = true;
	canUseExplore = true;
	canCommunicate = true;

	if (disciples.Num() < 60) {
		int32 count = 100 - disciples.Num();
		for (int32 i = 0; i < count; i++) {
			FDisciple temp;
			temp.SetEnemy();
			disciples.Emplace(temp);
		}
	}
	
	if (disciples.Num() < 100) {
		int32 random = FMath::RandRange(1, 100);
		if (random <= 20) {
			FDisciple temp;
			temp.SetEnemy();
			disciples.Emplace(temp);
		}
	}
}

void UEnemySect::AddFriendly(int32 point) {
	friendly += point;
	if (friendly > 200)
		friendly = 200;
}

FSaveESect UEnemySect::Save() {
	FSaveESect temp;
	temp.name = name;
	temp.sectLevel = sectLevel;
	temp.health = health;
	temp.attack = attack;
	temp.defense = defense;
	temp.disciples = disciples;
	temp.friendly = friendly;
	temp.canGiveGift = canGiveGift;
	temp.canUseAlienate = canUseAlienate;
	temp.canUseExplore = canUseExplore;
	temp.canCommunicate = canCommunicate;
	temp.hadAnnexed = hadAnnexed;
	temp.allianced = allianced;
	return temp;
}

void UEnemySect::Load(FSaveESect save) {
	name = save.name;
	sectLevel = save.sectLevel;
	health = save.health;
	attack = save.attack;
	defense = save.defense;
	disciples = save.disciples;
	friendly = save.friendly;
	canGiveGift = save.canGiveGift;
	canUseAlienate = save.canUseAlienate;
	canUseExplore = save.canUseExplore;
	canCommunicate = save.canCommunicate;
	hadAnnexed = save.hadAnnexed;
	allianced = save.allianced;
}

TArray<FDisciple> UEnemySect::GetFiveDis() {
	TArray<int32> num;
	TArray<int32> index;
	for (int32 i = 0; i < disciples.Num(); i++)
		num.Add(i);

	for (int32 i = 0; i < 5; i++) {
		int32 random = FMath::RandRange(0, num.Num() - 1);
		index.Add(num[random]);
		num.RemoveAt(random);
	}
	TArray<FDisciple> dis;
	for (int32 i = 0; i < 5; i++)
		dis.Emplace(disciples[index[i]]);

	return dis;
}

bool UEnemySect::CanGive(USect* sect) {
	if (canGiveGift == false || sect->spiritStone < 1000)
		return false;
	else
		return true;
}

bool UEnemySect::GiveGift(USect* sect) {
	canGiveGift = false;
	int32 random = FMath::RandRange(1, 100);
	bool successful = false;
	if (random <= 40)
		successful = false;

	else {
		sect->spiritStone -= 1000;
		AddFriendly(10);
		successful =  true;
	}
	sect->logs.Emplace(UEnemySectMessage::GiveGift(name, successful));
	sect->steamAchievement.CheckGiftAchievement();
	return successful;
}

bool UEnemySect::CanAlienate() {
	if (friendly >= 30 && canUseAlienate)
		return true;
	else
		return false;
}

bool UEnemySect::Alienate(USect* sect, int32 level) {
	friendly -= 30;
	canUseAlienate = false;
	int32 random = FMath::RandRange(1, 100);
	int32 p = 0;
	if (level > sectLevel)
		p = 80;
	else if (level == sectLevel)
		p = 60;
	else
		p = 20;

	bool successful = false;
	int32 nowNum = disciples.Num();

	if (random <= p) {
		Expel();
		successful = true;
	}
	else
		successful = false;

	nowNum -= disciples.Num();
	FText str = UEnemySectMessage::UseAlienate(name, nowNum, successful);
	sect->logs.Emplace(str);
	sect->steamAchievement.CheckAlienateAchievement();

	return successful;
}

void UEnemySect::Expel() {
	int32 expelDis = FMath::RandRange(1, 3);

	for (int32 i = 0; i < expelDis; i++) {
		int32 random = FMath::RandRange(0, disciples.Num() - 1);
		disciples.RemoveAt(random);
	}
}

bool UEnemySect::CanExplore() {
	if (friendly >= 60 && canUseExplore)
		return true;
	else
		return false;
}

bool UEnemySect::Explore(USect* sect, int32 level) {
	friendly -= 60;
	canUseExplore = false;
	int32 random = FMath::RandRange(1, 100);
	int32 p = 0;
	if (level > sectLevel)
		p = 100;
	else if (level == sectLevel)
		p = 70;
	else
		p = 50;

	bool successful = false;
	int32 nowNum = disciples.Num();

	if (random <= p) {
		Expel();
		successful = true;
	}
	else 
		successful = false;

	nowNum -= disciples.Num();
	FText str = UEnemySectMessage::UseExplore(name, nowNum, successful);
	sect->logs.Emplace(str);
	sect->steamAchievement.CheckExploreAchievement();

	return successful;
}

bool UEnemySect::IsAnnexed() {
	return hadAnnexed;
}

bool UEnemySect::CanAlliance() {
	return friendly >= 120 && !allianced;
}

void UEnemySect::Alliance() {
	allianced = true;
}

FText UEnemySectMessage::GiveGift(FText& name, bool successful) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(name.ToString()) };
	int32 rowIndex = 0;
	if (successful)
		rowIndex = 1;
	else
		rowIndex = 2;
	str = str.Format(*ReadSectMessage(rowIndex), args);
	return FText::FromString(*str);
}

FText UEnemySectMessage::UseAlienate(FText& name, int32 num, bool successful) {
	FString str = "";
	TArray<FStringFormatArg> arg1 = { FStringFormatArg(name.ToString()), FStringFormatArg(num) };
	TArray<FStringFormatArg> arg2 = { FStringFormatArg(name.ToString()) };

	if (successful)
		str = str.Format(*ReadSectMessage(3), arg1);
	else
		str = str.Format(*ReadSectMessage(4), arg2);

	return FText::FromString(*str);
}

FText UEnemySectMessage::UseExplore(FText& name, int32 num, bool successful) {
	FString str = "";
	TArray<FStringFormatArg> arg1 = { FStringFormatArg(name.ToString()), FStringFormatArg(num) };
	TArray<FStringFormatArg> arg2 = { FStringFormatArg(name.ToString()) };

	if (successful)
		str = str.Format(*ReadSectMessage(5), arg1);
	else
		str = str.Format(*ReadSectMessage(6), arg2);

	return FText::FromString(*str);
}

void FDemon::Create() {
	const char* path = "DataTable'/Game/DataTable/title/Demon.Demon'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		int32 row = FMath::RandRange(0, rowNames.Num() - 1);
		FReadText* data = pDataTable->FindRow<FReadText>(rowNames[row], "");
		if (data != NULL)
			name = data->str;
	}

	TArray<int32> healths = {3500000, 7200000, 10000000, 24000000, 48000000, 65000000, 100000000};
	TArray<int32> attacks = {1000000, 3400000, 7000000, 15000000, 26000000, 39000000, 60000000};
	TArray<int32> defenses = {900000, 3000000, 6800000, 14000000, 25000000, 38000000, 60000000};

	int32 m = gMapLevel;

	int32 min = healths[m] * 0.9;
	int32 max = healths[m] * 1.1;
	health = FMath::RandRange(min, max);

	min = attacks[m] * 0.9;
	max = attacks[m] * 1.1;
	attack = FMath::RandRange(min, max);

	min = defenses[m] * 0.9;
	max = defenses[m] * 1.1;
	defense = FMath::RandRange(min, max);
	
}
