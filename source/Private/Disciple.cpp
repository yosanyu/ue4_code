// Fill out your copyright notice in the Description page of Project Settings.


#include "Disciple.h"
#include "Constant.h"
#include "HandleLaw.h"
#include "HandleDisciple.h"
#include "HandleEquipment.h"

FWife::FWife() {
	name = FText();
	appearance = EAppearance::SSS; 
	personality = EWPersonality::SS;
	buff = 1.0;
	speed = 0;
	criticalP = 0;
	criticalStrike = 0.0;
}

void FWife::Create() {
	DecideName();
	DecideAppearance();
	DecidePersonality();
}

void FWife::DecideName() {
	auto GetText = [](int32 choice) {
		const char* path = GetDiscipleNamePath(choice);
		if (path != nullptr) {
			UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
			if (pDataTable != NULL) {
				TArray<FName> rowNames = pDataTable->GetRowNames();
				int32 random = FMath::RandRange(0, rowNames.Num() - 1);
				FName row = FName(*FString::FromInt(random));
				FReadText* data = pDataTable->FindRow<FReadText>(row, "");
				if (data != NULL) {
					return data->str;
				}
			}
		}
		return FText();
	};
	surname = GetText(1);
	name = GetText(3);
}

void FWife::DecideAppearance() {
	TArray<int32> p = { 1, 4, 9, 17, 27, 40, 60, 73, 83, 91, 96, 99, 100 };
	int32 random = FMath::RandRange(1, 100);
	for (int32 i = 0; i < p.Num(); i++) {
		if (random < p[i]) {
			appearance = EAppearance(i);
			break;
		}
	}
	int32 P = FMath::RandRange(1, 2);
	switch (appearance)
	{
	case EAppearance::SSS:
		SetBuff(0.2, 5, 0, 0.15);
		break;
	case EAppearance::SS:
		SetBuff(0.17, 4, 0, 0.13);
		break;
	case EAppearance::S:
		SetBuff(0.14, 3, 0, 0.11);
		break;
	case EAppearance::A:
		SetBuff(0.11, 2, 0, 0.09);
		break;
	case EAppearance::B:
		SetBuff(0.08, 1, 0, 0.07);
		break;
	case EAppearance::C:
		SetBuff(0.05, 0, 0, 0.05);
		break;
	case EAppearance::D:
		if(P == 1)
			SetBuff(0.05, 0, 0, 0.03);
		else
			SetBuff(-0.05, 0, 0, 0.03);
		break;
	case EAppearance::E:
		SetBuff(-0.05, 0, 5, 0.0);
		break;
	case EAppearance::F:
		SetBuff(-0.08, 4, 8, 0.0);
		break;
	case EAppearance::G:
		SetBuff(-0.11, 1, 11, 0.0);
		break;
	case EAppearance::H:
		SetBuff(-0.14, 1, 14, 0.0);
		break;
	case EAppearance::I:
		SetBuff(-0.17, 1, 17, 0.0);
		break;
	case EAppearance::J:
		SetBuff(-0.20, 1, 20, 0.0);
		break;
	default:
		break;
	}
	
}

void FWife::DecidePersonality() {
	int32 random = FMath::RandRange(0, 12);
	personality = EWPersonality(random);
	int32 P = FMath::RandRange(1, 2);
	switch (personality)
	{
	case EWPersonality::SSS:
		SetBuff(0.15, 2, 6, 0.05);
		break;
	case EWPersonality::SS:
		SetBuff(0.13, 2, 5, 0.05);
		break;
	case EWPersonality::S:
		SetBuff(0.11, 2, 4, 0.05);
		break;
	case EWPersonality::A:
		SetBuff(0.09, 1, 3, 0.05);
		break;
	case EWPersonality::B:
		SetBuff(0.07, 1, 2, 0.05);
		break;
	case EWPersonality::C:
		SetBuff(0.05, 1, 1, 0.05);
		break;
	case EWPersonality::D:
		if(P == 1)
			SetBuff(0.03, 0, 0, 0.03);
		else
			SetBuff(-0.03, 0, 0, 0.03);
		break;
	case EWPersonality::E:
		SetBuff(-0.05, 0, 2, 0.05);
		break;
	case EWPersonality::F:
		SetBuff(-0.07, 0, 4, 0.07);
		break;
	case EWPersonality::G:
		SetBuff(-0.09, 0, 6, 0.09);
		break;
	case EWPersonality::H:
		SetBuff(-0.11, 0, 8, 0.11);
		break;
	case EWPersonality::I:
		SetBuff(-0.13, 0, 10, 0.13);
		break;
	case EWPersonality::J:
		SetBuff(-0.15, 0, 12, 0.15);
		break;
	default:
		break;
	}
}

void FWife::SetBuff(float cbuff, int32 cspeed, int32 CP, float CS) {
	buff += cbuff;
	speed += cspeed;
	criticalP += CP;
	criticalStrike += CS;
}


FDisciple::FDisciple() {
	DecideRarity();
	DecideName();
	DecidePersonality();
	DecideBackground();
	DecideLifePalace();
	DecideStar();
	laws.SetNum(5);
	DecideAttribute();
	for (int32 i = 0; i < lifePalace; i++) {
		FCommonAttribute temp;
		lifeTreasures.Emplace(temp);
	}
	for (int32 i = 0; i < star; i++) {
		FStarSoul temp;
		starSouls.Emplace(temp);
	}
}

void FDisciple::DecideRarity() {
	int32 p = gDisP;
	TArray<int32> rarityP = { 1, 5, 14, 26, 52, 100 }; 	
	rarityP[0] += p;
	//rarityP[1] += p * 2;
	for (int32 i = 1; i < 5; i++)
		rarityP[i] += p * 2;

	int32 random = FMath::RandRange(1, 100);
	for (int32 i = 0; i < rarityP.Num(); i++) {
		if (random <= rarityP[i]) {
			rarity = EDiscipleRarityType(i);
			break;
		}
	}

}

void FDisciple::ResetRarity(EDiscipleRarityType r) {
	// 去除原來提供的屬性
	health -= lifePalace * 200;
	defense -= lifePalace * 60;
	attack -= star * 160;
	rarity = r;
	DecideLifePalace();
	DecideStar();
	// 加回提供的屬性
	health += lifePalace * 200;
	defense += lifePalace * 60;
	attack += star * 160;
	SetCultivateSpeed();
	if (married) {
		cultivateSpeed += wife.speed;
	}
	int32 times = lifePalace - lifeTreasures.Num();
	for (int32 i = 0; i < times; i++)
		lifeTreasures.Emplace(FCommonAttribute());
	times = star - starSouls.Num();
	for (int32 i = 0; i < times; i++)
		starSouls.Emplace(FStarSoul());

}

void FDisciple::DecideName() {

	auto GetText = [](int32 choice) {
		const char* path = GetDiscipleNamePath(choice);
		if (path != nullptr) {
			UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
			if (pDataTable != NULL) {
				TArray<FName> rowNames = pDataTable->GetRowNames();
				int32 random = FMath::RandRange(0, rowNames.Num() - 1);
				FName row = FName(*FString::FromInt(random));
				FReadText* data = pDataTable->FindRow<FReadText>(row, "");
				if (data != NULL) {
					return data->str;
				}
			}
		}
			return FText();
	};
	surname = GetText(1);
	name = GetText(2);

}

void FDisciple::DecidePersonality() {
	int32 random = FMath::RandRange(0, 4);
	personality = EPersonality(random);
}

void FDisciple::DecideBackground() {
	TArray<int32> backgroundP = {22, 37, 52, 69, 74, 92, 95, 100};
	int32 random = FMath::RandRange(1, 100);
	int32 choice = 0;
	for (int32 i = 0; i < backgroundP.Num(); i++) {
		if (random <= backgroundP[i]) {
			choice = i;
			break;
		}
	}
	background = EBackground(choice);
}

void FDisciple::DecideLifePalace() {
	int32 random;
	// 根據資質決定命宮數量
	switch (rarity) {
	case EDiscipleRarityType::SonofEra:
		random = FMath::RandRange(1, 100);
		if (random < 96)
			lifePalace = 12;
		else
			lifePalace = 13;
		break;
	case EDiscipleRarityType::Genius:
		random = FMath::RandRange(1, 100);
		if (random < 81)
			lifePalace = 10;
		else
			lifePalace = 11;
		break;
	case EDiscipleRarityType::Extraordinary:
		random = FMath::RandRange(7, 9);
		lifePalace = random;
		break;
	case EDiscipleRarityType::Outstanding:
		random = FMath::RandRange(5, 6);
		lifePalace = random;
		break;
	case EDiscipleRarityType::Excellent:
		random = FMath::RandRange(2, 4);
		lifePalace = random;
		break;
	case EDiscipleRarityType::Normal:
		lifePalace = 1;
		break;
	default:
		break;
	}
}

void FDisciple::DecideStar() {
	switch (rarity)
	{
	case EDiscipleRarityType::SonofEra:
		star = FMath::RandRange(8, 9);
		break;
	case EDiscipleRarityType::Genius:
		star = FMath::RandRange(7, 8);
		break;
	case EDiscipleRarityType::Extraordinary:
		star = FMath::RandRange(5, 6);
		break;
	case EDiscipleRarityType::Outstanding:
		star = FMath::RandRange(3, 4);
		break;
	case EDiscipleRarityType::Excellent:
		star = FMath::RandRange(2, 3);
		break;
	case EDiscipleRarityType::Normal:
		star = FMath::RandRange(1, 2);
		break;
	default:
		break;
	}
}

void FDisciple::DecideAttribute() {
	SetCultivateSpeed();
	year = FMath::RandRange(18, 25);
	criticalP = 10;
	criticalStrike = 0.1;
	health += lifePalace * 200;
	defense += lifePalace * 60;
	attack += star * 160;
}

void FDisciple::SetCultivateSpeed() {
	int32 base = 20;
	cultivateSpeed = base + lifePalace + star;
}

void FDisciple::Update(int32 speed) {
	yearAteElixirs = 0;
	CultivateLaw(speed);
	Practice();
	if (background == EBackground::OWVisit)
		RiseRarity();
}

void FDisciple::AddAttribute(int32 h, int32 a, int32 d) {
	int32 max = 500000;
	if (health + h > max)
		health = max;
	else
		health += h;
	if (attack + a > max)
		attack = max;
	else
		attack += a;
	if (defense + d > max)
		defense = max;
	else
		defense += d;
}

bool FDisciple::IsAttribute() {
	int32 max = 500000;
	bool a = (health >= max && attack >= max);
	bool b = (a && defense >= max);
	return b;
}

void FDisciple::CultivateLaw(int32 speed) {
	TArray<int32> values = {};
	for (int32 i = 0; i < 3; i++)
		values.Emplace(FMath::RandRange(15, 30));
	AddAttribute(values[0], values[1], values[2]);
	// 修煉所有功法
	for (auto& i : laws) {
		if (UHandleLaw::HasLaw(i) && i.CanLevelUp()) {	// 此位置已有功法且還沒滿級
			i.exp += cultivateSpeed + speed;	// 進行修煉
			i.LevelUp();	// 檢查能否升級
			if (!i.CanLevelUp()) {	// 檢查完若升至10級添加記錄
				FText str = UDiscipleMessage::LawToLimit(i, year);
				logs.Add(str);
			}
	
		}
	}
}

void FDisciple::Practice() {
	// 檢查境界是否還沒到上限
	if (level < 10) {
		// 已可進階 嘗試進階
		if (practice >= GetNextExp()) {
			if (CanLevelUp()) {
				LevelUp();
			}
		}
		else {
		// 還不可進階 經過今年修煉滿足可進階就嘗試進階
			practice += cultivateSpeed;
			if (practice >= GetNextExp()) {
				if (CanLevelUp()) {
					LevelUp();
				}
			}
		}
	}
	switch (level)
	{
	case 0:
		//60
		death = year > 60;   // 煉氣 
		break;
	case 1:
		death = year > 100;  // 築基
		break;
	case 2:
		death = year > 150;  // 金丹
		break;
	case 3:
		death = year > 300;  // 元嬰
		break;
	case 4:
		death = year > 500;  // 化神
		break;
	case 5:
		death = year > 800;  // 煉虛
		break;
	case 6:
		death = year > 1200; // 大乘
	break;
	default:
		break;
	}
}

void FDisciple::RiseRarity() {
	int32 random = FMath::RandRange(1, 100);
	EDiscipleRarityType r = rarity;
	switch (r)
	{
	case EDiscipleRarityType::SonofEra:
		break;
	case EDiscipleRarityType::Genius:
		if (random == 1) {
			ResetRarity(EDiscipleRarityType::SonofEra);
		}
		break;
	case EDiscipleRarityType::Extraordinary:
		if (random <= 5) {
			ResetRarity(EDiscipleRarityType::Genius);
		}
		break;
	case EDiscipleRarityType::Outstanding:
		if (random <= 20) {
			ResetRarity(EDiscipleRarityType::Extraordinary);
		}
		break;
	case EDiscipleRarityType::Excellent:
		if (random <= 40) {
			ResetRarity(EDiscipleRarityType::Outstanding);
		}
		break;
	case EDiscipleRarityType::Normal:
		if (random <= 70) {
			ResetRarity(EDiscipleRarityType::Excellent);
		}
		break;
	default:
		break;
	}
}

int32 FDisciple::GetNextExp() {
	//					   築基 金丹  元嬰  化神   煉虛  大乘
	TArray<int32> exps = { 700, 900, 1100, 3100, 4650, 5000, 4400, 8800, 11000, 22000};
	return exps[level];
}

bool FDisciple::CanLevelUp() {
	//level == gMapLevel + 2 ||
	if (level == 10)
		return false;

	TArray<int32> p = { 60, 50, 45, 40, 30, 25, 20, 15, 10, 1 };

	int32 random = FMath::RandRange(1, 100);
	if (random <= p[level])
		return true;
	return false;
}

void FDisciple::LevelUp() {
	practice = 0;
	TArray<int32> p = { 500, 1500, 2000, 2500, 3000, 4000, 6000, 10000, 20000, 50000 };
	AddAttribute(p[level], p[level], p[level]);
	++level;
	FText str = UDiscipleMessage::LevelUp(level, year);
	logs.Add(str);
}

void FDisciple::Marry() {
	married = true;
	Combination();
	cultivateSpeed += wife.speed;
	criticalP += wife.criticalP;
	criticalStrike += wife.criticalStrike;
}

void FDisciple::Combination() {
	if (personality == EPersonality::Timid) {
		switch (wife.personality)
		{
		case EWPersonality::S:
			wife.speed += 3;
			wife.buff += 0.03;
			break;
		case EWPersonality::F:
			wife.criticalP -= 3;
			wife.criticalStrike += 0.05;
			break;
		default:
			break;
		}
	}
	else if (personality == EPersonality::Kindness) {
		switch (wife.personality)
		{
		case EWPersonality::A:
			wife.speed += 3;
			wife.buff += 0.03;
			break;
		case EWPersonality::F:
			wife.speed += 2;
			wife.buff += 0.02;
			break;
		case EWPersonality::G:
			wife.buff -= 0.05;
			wife.criticalP += 3;
			wife.criticalStrike += 0.05;
			break;
		default:
			break;
		}
	}
	else if (personality == EPersonality::Ferocious) {
		switch (wife.personality)
		{
		case EWPersonality::G:
			wife.speed += 1;
			wife.buff += 0.01;
			wife.criticalP += 1;
			wife.criticalStrike += 0.01;
			break;
		case EWPersonality::H:
			wife.speed += 3;
			wife.buff += 0.03;
			wife.criticalP += 3;
			wife.criticalStrike += 0.05;
			break;
		case EWPersonality::I:
			wife.speed += 2;
			wife.buff += 0.02;
			break;
		case EWPersonality::J:
			wife.buff += 0.05;
			wife.criticalP += 3;
			wife.criticalStrike += 0.05;
			break;
		default:
			break;
		}
	}
	else if (personality == EPersonality::Careful) {
		switch (wife.personality)
		{
		case EWPersonality::SS:
			wife.speed += 3;
			wife.buff += 0.03;
			wife.criticalP += 3;
			wife.criticalStrike += 0.03;
			break;
		case EWPersonality::S:
			wife.speed += 2;
			wife.buff += 0.02;
			wife.criticalP += 2;
			wife.criticalStrike += 0.02;
			break;
		case EWPersonality::B:
			wife.speed += 5;
			wife.buff += 0.05;
			wife.criticalP += 5;
			wife.criticalStrike += 0.05;
			break;
		default:
			break;
		}
	}
	else if (personality == EPersonality::Cruel) {
		switch (wife.personality)
		{
		case EWPersonality::F:
			wife.speed += 4;
			wife.buff += 0.04;
			wife.criticalP += 4;
			wife.criticalStrike += 0.04;
			break;
		case EWPersonality::G:
			wife.speed += 8;
			wife.buff += 0.08;
			wife.criticalP += 8;
			wife.criticalStrike += 0.08;
			break;
		default:
			break;
		}
	}
}

void FDisciple::Divorce() {
	cultivateSpeed -= wife.speed;
	criticalP -= wife.criticalP;
	criticalStrike -= wife.criticalStrike;
	married = false;
	FWife nWife;
	wife = nWife;
}

int32 FDisciple::GetDamage() {
	int32 allDamage = 0;
	int32 damage = UHandleDisciple::GetDamage(*this);

	TArray<FEquipment> es;
	if (UHandleEquipment::HasEquipment(weapon))
		es.Emplace(weapon);
	if (UHandleEquipment::HasEquipment(artifact))
		es.Emplace(artifact);
	if (UHandleEquipment::HasEquipment(hiddenWeapon))
		es.Emplace(hiddenWeapon);

	// 獨特詞綴攻擊兩次
	bool twiceAttack = UHandleEquipment::CanAttackTwice(es);
	// 獨特詞綴攻擊提升100%
	bool doubleAttack = UHandleEquipment::CanAttackRise(es);
	// 獨特詞綴必定爆擊
	bool mustCP = UHandleEquipment::IsMustCS(es);

	// 攻擊兩次
	if (twiceAttack) {
		for (int32 i = 0; i < 2; i++) {
			int32 cp = FMath::RandRange(1, 100);
			// 爆擊
			if (mustCP || cp <= criticalP)
				allDamage = allDamage + damage * (1.0 + criticalStrike);
			else
				allDamage += damage;
		}
	}
	// 攻擊一次
	else {
		int32 cp = FMath::RandRange(1, 100);
		// 爆擊
		if (mustCP || cp <= criticalP)
			allDamage = allDamage + damage * (1.0 + criticalStrike);
		else
			allDamage += damage;
	}

	if (doubleAttack)
		allDamage *= 2;

	
	if (background == EBackground::Outcast)
		allDamage *= 1.1;

	return allDamage;
}

int32 FDisciple::GetDefense() {
	int32 value = UHandleDisciple::GetDefense(*this);
	TArray<FEquipment> es;

	if (UHandleEquipment::HasEquipment(weapon))
		es.Emplace(weapon);
	if (UHandleEquipment::HasEquipment(artifact))
		es.Emplace(artifact);
	if (UHandleEquipment::HasEquipment(hiddenWeapon))
		es.Emplace(hiddenWeapon);

	if (UHandleEquipment::CanDefenseRise(es))
		value *= 2;

	return value;

}

void FDisciple::SetEnemy() {
	// 敵人穿裝備
	int32 m = gMapLevel;
	TArray<int32> dLevel = { 3, 4, 5, 6, 7, 8, 10 };
	//100, 200, 300, 400, 500, 750, 1000, 1400, 1800, 4000
	TArray<int32> levelAttribute = {600, 1000, 1500, 2250, 3250, 4650, 10450 };
	TArray<int32> minAttribute = { 1500, 5000, 9000, 15000, 30000, 80000, 150000 };
	TArray<int32> maxlAttribute = { 2000, 7500, 12000, 18000, 60000, 120000, 200000 };
	TArray<EItemRarityType> rType = {
		EItemRarityType(3), EItemRarityType(3), EItemRarityType(3), EItemRarityType(2),
		EItemRarityType(2), EItemRarityType(1), EItemRarityType(0)
	};
	TArray<int32> eLevel = { 10, 18, 25, 10, 20, 15, 10 };

	TArray<int32> lawMin = { 406, 292, 193, 117, 59, 21, 0 };
	TArray<int32> lawMax = { 552, 405, 291, 192, 116, 58, 20 };

	FEquipment w, a, h;
	w.Create(EEquipmentType::Weapon, rType[m], eLevel[m]);
	a.Create(EEquipmentType::Artifact, rType[m], eLevel[m]);
	h.Create(EEquipmentType::HiddenWeapon, rType[m], eLevel[m]);
	weapon = w;
	artifact = a;
	hiddenWeapon = h;
	level = dLevel[m];

	AddAttribute(levelAttribute[m], levelAttribute[m], levelAttribute[m]);
	TArray<int32> attributes;
	for (int32 i = 0; i < 3; i++) {
		int32 temp = FMath::RandRange(minAttribute[m], maxlAttribute[m]);
		attributes.Emplace(temp);
	}
	AddAttribute(attributes[0], attributes[1], attributes[2]);
	
	// 敵人修煉功法
	const char* path = "DataTable'/Game/DataTable/Law/Law.Law'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	for (int32 i = 0; i < 5; i++) {
		if (pDataTable != NULL) {
			int32 law = FMath::RandRange(lawMin[m], lawMax[m]);
			FLaw* temp = pDataTable->FindRow<FLaw>(FName(*FString::FromInt(law)), "");
			if (temp != NULL) {
				laws[i] = *temp;
				laws[i].lawLevel = 10;
			}
		}
	}
}

void FDisciple::UseElixirs(FElixirs elixirs) {
	int32* usedNum = usedElixirs.Find(elixirs);
	if (usedNum == nullptr) {
		usedElixirs.Emplace(elixirs, 1);
	}
	else
		*usedNum += 1;
	EElixirsType type = elixirs.type;
	switch (type)
	{
	case EElixirsType::Health:
		AddElixirH(elixirs.value);
		break;
	case EElixirsType::Attack:
		AddElixirA(elixirs.value);
		break;
	case EElixirsType::Defense:
		AddElixirD(elixirs.value);
		break;
	case EElixirsType::All:
		AddElixirH(elixirs.value);
		AddElixirA(elixirs.value);
		AddElixirD(elixirs.value);
		break;
	case EElixirsType::Rarity:
		break;
	default:
		break;
	}
	++ateElixirs;
	++yearAteElixirs;
}

void FDisciple::AddElixirH(int32 v) {
	int32 max = 100000;
	if (elixirHealth + v >= max)
		elixirHealth = max;
	else
		elixirHealth += v;
}

void FDisciple::AddElixirA(int32 v) {
	int32 max = 100000;
	if (elixirAttack + v >= max)
		elixirAttack = max;
	else
		elixirAttack += v;
}

void FDisciple::AddElixirD(int32 v) {
	int32 max = 100000;
	if (elixirDefense + v >= max)
		elixirDefense = max;
	else
		elixirDefense += v;
}

void FDisciple::SetLifeTreasure(int32 index, FCommonAttribute temp) {
	lifeTreasures[index] = temp;
	extraHealth  += temp.health;
	extraAttack  += temp.attack;
	extraDefense += temp.defense;
}

void FDisciple::SetStarSoul(int32 index, FStarSoul temp) {
	starSouls[index] = temp;
	switch (temp.type)
	{
	case EAffix::H5:
		extraHealth += temp.value;
		break;
	case EAffix::A5:
		extraAttack += temp.value;
		break;
	case EAffix::D5:
		extraDefense += temp.value;
		break;
	case EAffix::CriticalP:
		criticalP += temp.value;
		break;
	case EAffix::CriticalStrike:
		criticalStrike += (float(temp.value) * 1.0 * 0.01);
		break;
	default:
		break;
	}
}
