// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleDisciple.h"
#include "HandleEquipment.h"
#include "HandleLaw.h"
#include "HandleBody.h"
#include "Constant.h"

FString Read(int32 index) {
	const char* path = "DataTable'/Game/DataTable/Message/DisMessage.DisMessage'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FReadText* data = pDataTable->FindRow<FReadText>(FName(*FString::FromInt(index)), "");
		if (data != NULL) {
			return data->str.ToString();
		}
	}
	return FString();
}

void UHandleDisciple::AddDisciple(USect* sect) {
	FDisciple temp;
	sect->disciples.Emplace(temp);
	if (gDisP < 4) {
		++sect->shop.disTimes;
		if (sect->shop.disTimes == 150) {
			sect->shop.disTimes = 0;
			++gDisP;
		}
	}
	sect->steamAchievement.ChcekDiscipleAchievement(temp.rarity);
}

bool UHandleDisciple::SpiritStoneEnough(USect* sect) {
	return sect->spiritStone >= 500;
}

bool UHandleDisciple::CanRecruitDisciple(USect* sect) {
	return sect->disciples.Num() < sect->discipleMax;
}

void UHandleDisciple::RecruitDisciple(USect* sect) {
	sect->spiritStone -= 500;
	AddDisciple(sect);
}

void UHandleDisciple::RecruitDisciples(USect* sect) {
	int32 times = sect->discipleMax - sect->disciples.Num();
	for (int32 i = 0; i < times; i++) {
		if (SpiritStoneEnough(sect)) {
			if (CanRecruitDisciple(sect))
				RecruitDisciple(sect);
		}
	}
}

void UHandleDisciple::Sort(USect* sect) {
	sect->disciples.StableSort([](const FDisciple& A, const FDisciple& B) {
		/*
			弟子排序先比資質
			相同再比命宮數量
			相同再比星辰數量
		*/
		/**
		if (A.rarity == B.rarity) {
			if (A.lifePalace == B.lifePalace)
				return A.star > B.star;
			else
				return A.lifePalace > B.lifePalace;
		}
		*/
		if (A.rarity == B.rarity) {
			if (A.lifePalace == B.lifePalace) {
				if (A.star == B.star) {
					if (A.personality == B.personality)
						return A.background < B.background;
					else
						return A.personality < B.personality;
				}
				else return A.star > B.star;
			}
			else
				return A.lifePalace > B.lifePalace;
		}
		return A.rarity < B.rarity;
	});
}

void UHandleDisciple::ExpelSeveral(USect* sect, const TArray<int32>& indexs) {
	int32 count = 0;
	for (int32 i = 0; i < indexs.Num(); i++) {
		Expel(sect, indexs[i] - count);
		++count;
	}
}

void UHandleDisciple::Expel(USect* sect, int32 index) {
	FDisciple temp = sect->disciples[index];

	if (UHandleEquipment::HasEquipment(temp.weapon))
		sect->weapons.Emplace(temp.weapon);

	if (UHandleEquipment::HasEquipment(temp.artifact))
		sect->artifacts.Emplace(temp.artifact);

	if (UHandleEquipment::HasEquipment(temp.hiddenWeapon))
		sect->hiddenWeapons.Emplace(temp.hiddenWeapon);

	if (UHandleBody::HasOrgan(temp.body.hand))
		sect->hands.Emplace(temp.body.hand);

	if (UHandleBody::HasOrgan(temp.body.foot))
		sect->foots.Emplace(temp.body.foot);

	if (UHandleBody::HasOrgan(temp.body.heart))
		sect->hearts.Emplace(temp.body.heart);

	if (UHandleBody::HasOrgan(temp.body.lung))
		sect->lungs.Emplace(temp.body.lung);

	if (UHandleBody::HasOrgan(temp.body.kidney))
		sect->kidneys.Emplace(temp.body.kidney);

	if (!sect->disciples[index].death)
		sect->steamAchievement.CheckExpelDiscipleAchievement();

	sect->disciples.RemoveAt(index);
}

void UHandleDisciple::UseEquipment(USect* sect, int32 disIndex, int32 equipIndex, EEquipmentType type) {
	switch (type)
	{
	case EEquipmentType::Weapon:
		if(UHandleEquipment::HasEquipment(sect->disciples[disIndex].weapon)) 
			sect->weapons.Emplace(sect->disciples[disIndex].weapon);
		sect->disciples[disIndex].weapon = sect->weapons[equipIndex];
		sect->weapons.RemoveAt(equipIndex);
		break;
	case EEquipmentType::Artifact:
		if (UHandleEquipment::HasEquipment(sect->disciples[disIndex].artifact))
			sect->artifacts.Emplace(sect->disciples[disIndex].artifact);
		sect->disciples[disIndex].artifact = sect->artifacts[equipIndex];
		sect->artifacts.RemoveAt(equipIndex);
		break;
	case EEquipmentType::HiddenWeapon:
		if (UHandleEquipment::HasEquipment(sect->disciples[disIndex].hiddenWeapon))
			sect->hiddenWeapons.Emplace(sect->disciples[disIndex].hiddenWeapon);
		sect->disciples[disIndex].hiddenWeapon = sect->hiddenWeapons[equipIndex];
		sect->hiddenWeapons.RemoveAt(equipIndex);
		break;
	default:
		break;
	}
}

void UHandleDisciple::UseEquipments(USect* sect, int32 disIndex) {
	if (HasEquipment(sect, disIndex, EEquipmentType::Weapon))
		RemoveEquipment(sect, disIndex, EEquipmentType::Weapon);
	if (HasEquipment(sect, disIndex, EEquipmentType::Artifact))
		RemoveEquipment(sect, disIndex, EEquipmentType::Artifact);
	if (HasEquipment(sect, disIndex, EEquipmentType::HiddenWeapon))
		RemoveEquipment(sect, disIndex, EEquipmentType::HiddenWeapon);

	for (int32 i = 1; i < 4; i++)
		UHandleEquipment::Sort(sect, i);

	if (sect->weapons.Num() > 0) 
		UseEquipment(sect, disIndex, 0, EEquipmentType::Weapon);
	if (sect->artifacts.Num() > 0)
		UseEquipment(sect, disIndex, 0, EEquipmentType::Artifact);
	if (sect->hiddenWeapons.Num() > 0)
		UseEquipment(sect, disIndex, 0, EEquipmentType::HiddenWeapon);
}

void UHandleDisciple::SellEquipment(USect* sect, int32 index, EEquipmentType type) {
	FEquipment temp;
	switch (type)
	{
	case EEquipmentType::Weapon:
		sect->spiritStone += sect->disciples[index].weapon.price;
		sect->disciples[index].weapon = temp;
		break;
	case EEquipmentType::Artifact:
		sect->spiritStone += sect->disciples[index].artifact.price;
		sect->disciples[index].artifact = temp;
		break;
	case EEquipmentType::HiddenWeapon:
		sect->spiritStone += sect->disciples[index].hiddenWeapon.price;
		sect->disciples[index].hiddenWeapon = temp;
		break;
	default:
		break;
	} 
}

void UHandleDisciple::RemoveEquipment(USect* sect, int32 disIndex, EEquipmentType type) {
	FEquipment temp;
	switch (type)
	{
	case EEquipmentType::Weapon:
		sect->weapons.Emplace(sect->disciples[disIndex].weapon);
		sect->disciples[disIndex].weapon = temp;
		break;
	case EEquipmentType::Artifact:
		sect->artifacts.Emplace(sect->disciples[disIndex].artifact);
		sect->disciples[disIndex].artifact = temp;
		break;
	case EEquipmentType::HiddenWeapon:
		sect->hiddenWeapons.Emplace(sect->disciples[disIndex].hiddenWeapon);
		sect->disciples[disIndex].hiddenWeapon = temp;
		break;
	default:
		break;
	}
}

bool UHandleDisciple::HasEquipment(USect* sect, int32 disIndex, EEquipmentType type) {
	switch (type)
	{
	case EEquipmentType::Weapon:
		return UHandleEquipment::HasEquipment(sect->disciples[disIndex].weapon);
		break;
	case EEquipmentType::Artifact:
		return UHandleEquipment::HasEquipment(sect->disciples[disIndex].artifact);
		break;
	case EEquipmentType::HiddenWeapon:
		return UHandleEquipment::HasEquipment(sect->disciples[disIndex].hiddenWeapon);
		break;
	default:
		return false;
		break;
	}
}

bool UHandleDisciple::RarityCanLearn(const FDisciple& dis, const FLaw& law) {
	if (uint8(law.rarity) >= uint8(dis.rarity))
		return true;
	else
		return false;
}

bool UHandleDisciple::CanUseElixirs(FDisciple dis) {
	int32 max = 100000;
	if (dis.elixirHealth == max && dis.elixirAttack == max && dis.elixirDefense == max)
		return false;

	if (dis.yearAteElixirs == 10)
		return false;
	else
		return true;
}

void UHandleDisciple::UseElixirs(USect* sect, int32 disIndex, FElixirs elixirs) {
	int32* temp = sect->elixirs.Find(elixirs);
	if (temp != nullptr && *temp > 0) {
		*temp -= 1;
		sect->disciples[disIndex].UseElixirs(elixirs);
	}
}

bool UHandleDisciple::UseRarityPill(USect* sect, int32 disIndex, FElixirs elixirs) {
	int32* num = sect->elixirs.Find(elixirs);
	if (num != nullptr) {
		if (*num == 0)
			return false;

		*num -= 1;
		int32 random = FMath::RandRange(1, 100);
		EDiscipleRarityType r = sect->disciples[disIndex].rarity;
		switch (r)
		{
		case EDiscipleRarityType::SonofEra:
			return false;
			break;
		case EDiscipleRarityType::Genius:
			if (random == 1) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::SonofEra);
				return true;
			}
			break;
		case EDiscipleRarityType::Extraordinary:
			if (random <= 5) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Genius);
				return true;
			}
			break;
		case EDiscipleRarityType::Outstanding:
			if (random <= 20) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Extraordinary);
				return true;
			}
			break;
		case EDiscipleRarityType::Excellent:
			if (random <= 40) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Outstanding);
				return true;
			}
			break;
		case EDiscipleRarityType::Normal:
			if (random <= 70) {
				sect->disciples[disIndex].ResetRarity(EDiscipleRarityType::Excellent);
				return true;
			}
			break;
		default:
			return false;
			break;
		}
	}
	return false;
}

void UHandleDisciple::SortElixirs(USect* sect, int32 disIndex) {
	sect->disciples[disIndex].usedElixirs.KeySort([](FElixirs A, FElixirs B) {
		return A.id < B.id;
	});
}

bool UHandleDisciple::CanLearnLaw(USect* sect, int32 disIndex, FLaw law) {
	for (int32 i = 0; i < 5; i++) {
		if (sect->disciples[disIndex].laws[i].id == law.id) {
			return false;
		}
	}
	return true;
}

void UHandleDisciple::LearnLaw(USect* sect, int32 disIndex, FLaw law, int32 index) {
	//FText log = FText();
	//if (UHandleLaw::HasLaw(sect->disciples[disIndex].laws[index])) {
	//	log = UDiscipleMessage::LearnNewLaw(sect->disciples[disIndex].laws[index], sect->disciples[disIndex].year);
	//	sect->disciples[disIndex].logs.Add(log);
	//}

	sect->disciples[disIndex].laws[index] = law;
	//log = UDiscipleMessage::LearnLaw(law, sect->disciples[disIndex].year);
	//sect->disciples[disIndex].logs.Add(log);
}

void UHandleDisciple::LearnLaws(USect* sect, int32 disIndex) {
	UHandleLaw::Sort(sect);
	TArray<FLaw> H, A, D;
	TArray<EItemRarityType> limit;
	for (int32 i = 0; i < 6; i++)
		limit.Emplace(EItemRarityType(i));

	for (auto& i : sect->hadLaws) {
		int32 r = uint8(sect->disciples[disIndex].rarity);
		if (i.rarity >= limit[r]) {
			if (i.health > 0)
				H.Emplace(i);
			else if (i.attack > 0)
				A.Emplace(i);
			else
				D.Emplace(i);
		}
	}

	for (int32 i = 0; i < 3; i++) {
		if (H.Num() == 0)
			break;
		if (!UHandleLaw::HasLaw(sect->disciples[disIndex].laws[i])) {
			if (CanLearnLaw(sect, disIndex, H[0])) {
				LearnLaw(sect, disIndex, H[0], i);
				H.RemoveAt(0);
			}
		}
		else {
			int32 min = FMath::Min(3 - i, H.Num());
			bool contiuneLoop = false;
			int32 count = 0;
			for (int32 j = 0; j < min; j++) {
				// H[j - count]
				//if (!CanLearnLaw(sect, disIndex, H[j - count]))
				if (sect->disciples[disIndex].laws[i].id == H[j].id) {
					H.RemoveAt(j);
					//++count;
					contiuneLoop = true;
					break;
				}
			}
			if (contiuneLoop)
				continue;
			// rarity
			if (CanLearnLaw(sect, disIndex, H[0]) && H[0].id < sect->disciples[disIndex].laws[i].id) {
				LearnLaw(sect, disIndex, H[0], i);
				H.RemoveAt(0);
			}
		}
	}

	TArray<FLaw> needSort;
	for (int32 i = 0; i < 3; i++)
		needSort.Emplace(sect->disciples[disIndex].laws[i]);

	needSort.Sort([](const FLaw& A, const FLaw& B) {
		return A.id < B.id;
	});

	for (int32 i = 0; i < 3; i++)
		sect->disciples[disIndex].laws[i] = needSort[i];

	if (A.Num() != 0) {
		if (!UHandleLaw::HasLaw(sect->disciples[disIndex].laws[3])) {
			if (CanLearnLaw(sect, disIndex, A[0])) {
				LearnLaw(sect, disIndex, A[0], 3);
				A.RemoveAt(0);
			}
		}
		else {
			if (CanLearnLaw(sect, disIndex, A[0])) {
				LearnLaw(sect, disIndex, A[0], 3);
				A.RemoveAt(0);
			}
		}
	}

	if (D.Num() != 0) {
		if (!UHandleLaw::HasLaw(sect->disciples[disIndex].laws[4])) {
			if (CanLearnLaw(sect, disIndex, D[0])) {
				LearnLaw(sect, disIndex, D[0], 4);
				D.RemoveAt(0);
			}
		}
		else {
			if (CanLearnLaw(sect, disIndex, D[0])) {
				LearnLaw(sect, disIndex, D[0], 4);
				D.RemoveAt(0);
			}
		}
	}
}

TArray<FLaw> UHandleDisciple::GetLaws(FDisciple dis) {
	return dis.laws;
}

int32 UHandleDisciple::GetCultivateSpeed(USect* sect, FDisciple dis) {
	return sect->speed + dis.cultivateSpeed;
}

bool UHandleDisciple::IsMarried(FDisciple dis) {
	return dis.married;
}

void UHandleDisciple::Marry(USect* sect, int32 index, FWife wife) {
	sect->disciples[index].wife = wife;
	sect->disciples[index].Marry();
	FText str = UDiscipleMessage::GetMarry(wife.surname, wife.name, sect->disciples[index].year);
	sect->disciples[index].logs.Add(str);
}

void UHandleDisciple::Divorce(USect* sect, int32 index) {
	FWife temp = sect->disciples[index].wife;
	FText str = UDiscipleMessage::GetDivorce(temp.surname, temp.name, sect->disciples[index].year);
	sect->disciples[index].logs.Add(str);
	sect->disciples[index].Divorce();
}

void UHandleDisciple::UseOrgan(USect* sect, int32 disIndex, EOrganType type, int32 OrganIndex) {
	FOrgan temp;
	FDisciple& dis = sect->disciples[disIndex];
	switch (type)
	{
	case EOrganType::Hand:
		temp = sect->hands[OrganIndex];
		if (UHandleBody::HasOrgan(dis.body.hand))
			sect->hands.Emplace(dis.body.hand);
		dis.body.hand = temp;
		sect->hands.RemoveAt(OrganIndex);
		break;
	case EOrganType::Foot:
		temp = sect->foots[OrganIndex];
		if (UHandleBody::HasOrgan(dis.body.foot))
			sect->foots.Emplace(dis.body.foot);
		dis.body.foot = temp;
		sect->foots.RemoveAt(OrganIndex);
		break;
	case EOrganType::Heart:
		temp = sect->hearts[OrganIndex];
		if (UHandleBody::HasOrgan(dis.body.heart))
			sect->hearts.Emplace(dis.body.heart);
		dis.body.heart = temp;
		sect->hearts.RemoveAt(OrganIndex);
		break;
	case EOrganType::Lung:
		temp = sect->lungs[OrganIndex];
		if (UHandleBody::HasOrgan(dis.body.lung))
			sect->lungs.Emplace(dis.body.lung);
		dis.body.lung = temp;
		sect->lungs.RemoveAt(OrganIndex);
		break;
	case EOrganType::Kidney:
		temp = sect->kidneys[OrganIndex];
		if (UHandleBody::HasOrgan(dis.body.kidney))
			sect->kidneys.Emplace(dis.body.kidney);
		dis.body.kidney = temp;
		sect->kidneys.RemoveAt(OrganIndex);
		break;
	default:
		break;
	}
}

void UHandleDisciple::UseOrgans(USect* sect, int32 disIndex) {
	for (int32 i = 0; i < 5; i++) {
		if(HasTypeOrgan(sect->disciples[disIndex], EOrganType(i)))
			UHandleBody::Remove(sect, disIndex, EOrganType(i));
		UHandleBody::SortOrgan(sect, EOrganType(i));
		if (UHandleBody::GetNums(sect, EOrganType(i)) > 0)
			UseOrgan(sect, disIndex, EOrganType(i), 0);
	}
}

bool UHandleDisciple::HasTypeOrgan(const FDisciple& dis, EOrganType type) {
	switch (type)
	{
	case EOrganType::Hand:
		if (UHandleBody::HasOrgan(dis.body.hand))
			return true;
		break;
	case EOrganType::Foot:
		if (UHandleBody::HasOrgan(dis.body.foot))
			return true;
		break;
	case EOrganType::Heart:
		if (UHandleBody::HasOrgan(dis.body.heart))
			return true;
		break;
	case EOrganType::Lung:
		if (UHandleBody::HasOrgan(dis.body.lung))
			return true;
		break;
	case EOrganType::Kidney:
		if (UHandleBody::HasOrgan(dis.body.kidney))
			return true;
		break;
	default:
		break;
	}
	return false;
}

TArray<FWife> UHandleDisciple::GetWifes() {
	TArray<FWife> wifes;
	wifes.SetNum(3);
	for (auto& i : wifes)
		i.Create();
	return wifes;
}

int32 UHandleDisciple::GetH5(FDisciple dis) {
	int32 value = dis.health;
	float buff = 1.0;
	// 獲取裝備%數加成
	buff += dis.weapon.GetHP();
	buff += dis.artifact.GetHP();
	buff += dis.hiddenWeapon.GetHP();

	// 獲取性格加成
	switch (dis.personality) {
	case EPersonality::Careful:
		buff += 0.15;
		break;
	case EPersonality::Timid:
		buff -= 0.10;
		break;
	default:
		break;
	}

	// 獲取出身背景加成
	switch (dis.background)
	{
	case EBackground::Noble:
		buff += 0.05;
		break;
	case EBackground::Royal:
		buff += 0.10;
		break;
	case EBackground::Rebirth:
		buff += 0.20;
		break;
	case EBackground::OWVisit:
		buff += 0.10;
		break;
	default:
		break;
	}

	// 獲取門派加成
	buff += gSectBuff;

	// 計算門派與道侶加成
	value *= (buff + dis.wife.buff - 1.0);

	// 計算裝備與丹藥額外屬性
	value += dis.weapon.GetH5();
	value += dis.artifact.GetH5();
	value += dis.hiddenWeapon.GetH5();
	value += dis.elixirHealth;
	value += dis.extraHealth;

	return value;
}

int32 UHandleDisciple::GetA5(FDisciple dis) {
	int32 value = dis.attack;
	float buff = 1.0;
	buff += dis.weapon.GetAP();
	buff += dis.artifact.GetAP();
	buff += dis.hiddenWeapon.GetAP();

	// 獲取性格加成
	switch (dis.personality) {
	case EPersonality::Ferocious:
		buff += 0.15;
		break;
	case EPersonality::Kindness:
		buff -= 0.10;
		break;
	case EPersonality::Timid:
		buff -= 0.10;
		break;
	default:
		break;
	}

	// 獲取出身背景加成
	switch (dis.background)
	{
	case EBackground::Military:
		buff += 0.15;
		break;
	case EBackground::Noble:
		buff += 0.05;
		break;
	case EBackground::Royal:
		buff += 0.10;
		break;
	case EBackground::Rebirth:
		buff += 0.20;
		break;
	case EBackground::OWVisit:
		buff += 0.10;
		break;
	default:
		break;
	}

	// 獲取門派加成
	buff += gSectBuff;

	value *= (buff + dis.wife.buff - 1.0);
	// 計算裝備與丹藥額外屬性
	value += dis.weapon.GetA5();
	value += dis.artifact.GetA5();
	value += dis.hiddenWeapon.GetA5();
	value += dis.elixirAttack;
	value += dis.extraAttack;

	return value;
}

int32 UHandleDisciple::GetD5(FDisciple dis) {
	int32 value = dis.defense;
	float buff = 1.0;
	buff += dis.weapon.GetDP();
	buff += dis.artifact.GetDP();
	buff += dis.hiddenWeapon.GetDP();

	// 獲取性格加成
	switch (dis.personality) {
	case EPersonality::Timid:
		buff -= 0.10;
		break;
	default:
		break;
	}

	// 獲取出身背景加成
	switch (dis.background)
	{
	case EBackground::Military:
		buff += 0.05;
		break;
	case EBackground::Noble:
		buff += 0.05;
		break;
	case EBackground::Royal:
		buff += 0.10;
		break;
	case EBackground::Rebirth:
		buff += 0.20;
		break;
	case EBackground::OWVisit:
		buff += 0.10;
		break;
	default:
		break;
	}

	// 獲取門派加成
	buff += gSectBuff;

	// 計算門派與道侶加成
	value *= (buff + dis.wife.buff - 1.0);
	// 計算裝備與丹藥額外屬性
	value += dis.weapon.GetD5();
	value += dis.artifact.GetD5();
	value += dis.hiddenWeapon.GetD5();
	value += dis.elixirDefense;
	value += dis.extraDefense;

	return value;
}

int32 UHandleDisciple::GetHealth(FDisciple dis) {
	int32 health = GetH5(dis) * 5;
	health += dis.body.GetHealth();
	health += dis.weapon.GetHealth();
	health += dis.artifact.GetHealth();
	health += dis.hiddenWeapon.GetHealth();
	for (auto& i : dis.laws)
		health += UHandleLaw::GetHealth(i);

	return health;
}

int32 UHandleDisciple::GetDamage(FDisciple dis) {
	int32 damage = GetA5(dis) * 5;
	damage += dis.body.GetDamage();
	damage += dis.weapon.GetAttack();
	damage += dis.artifact.GetAttack();
	damage += dis.hiddenWeapon.GetAttack();
	for (auto& i : dis.laws)
		damage += UHandleLaw::GetDamage(i);

	return damage;
}

int32 UHandleDisciple::GetDefense(FDisciple dis) {
	int32 defense = GetD5(dis) * 5;
	defense += dis.body.GetDefense();
	defense += dis.weapon.GetDefense();
	defense += dis.artifact.GetDefense();
	defense += dis.hiddenWeapon.GetDefense();
	for (auto& i : dis.laws)
		defense += UHandleLaw::GetDefense(i);

	return defense;
}

int32 UHandleDisciple::GetCP(FDisciple dis) {
	int32 p = dis.criticalP;
	if (dis.personality == EPersonality::Cruel)
		p += 10;
	p += dis.weapon.GetCP();
	p += dis.artifact.GetCP();
	p += dis.hiddenWeapon.GetCP();
	return p;
}

float UHandleDisciple::GetCS(FDisciple dis) {
	float p = dis.criticalStrike;
	p += dis.weapon.GetCS();
	p += dis.artifact.GetCS();
	p += dis.hiddenWeapon.GetCS();
	return p;
}

FText UHandleDisciple::AfterBattle(USect* sect, int32 index) {
	TArray<int32> attribute;
	for (int32 i = 0; i < 3; i++) {
		int32 random = FMath::RandRange(30, 60);
		attribute.Add(random);
	}
	sect->disciples[index].health += attribute[0];
	sect->disciples[index].attack += attribute[1];
	sect->disciples[index].defense += attribute[2];
	return UDiscipleMessage::GetAfterBattle(sect->disciples[index], attribute);
}

bool UHandleDisciple::IsSonofEra(FDisciple dis) {
	return dis.rarity == EDiscipleRarityType::SonofEra ? true : false;
}

FText UHandleDisciple::GetDiscipleNums(USect* sect) {
	FString str = "{0}/{1}";
	TArray<FStringFormatArg> args = {
		FStringFormatArg(sect->disciples.Num()),
		FStringFormatArg(sect->discipleMax)
	};
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::LearnLaw(FLaw& law, int32 year) {
	FString str = "";
	TArray<FStringFormatArg> args = {FStringFormatArg(year), FStringFormatArg(law.name.ToString()) };
	str = Read(uint8(law.rarity));
	str = FString::Format(*str, args);
	
	return FText::FromString(*str);
}

FText UDiscipleMessage::LearnNewLaw(FLaw& law, int32 year) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(year), FStringFormatArg(law.name.ToString()),};
	str = Read(uint8(law.rarity) + 7);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::LawToLimit(FLaw& law, int32 year) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(year), FStringFormatArg(law.name.ToString()), };
	str = Read(uint8(law.rarity) + 14);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::LevelUp(int32 level, int32 year) {
	const char* path = "DataTable'/Game/DataTable/Message/DisLevel.DisLevel'";
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(year)};
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		FReadText* data = pDataTable->FindRow<FReadText>(FName(*FString::FromInt(level)), "");
		if (data != NULL) {
			str = data->str.ToString();
			str = FString::Format(*str, args);
		}
	}
	return FText::FromString(*str);
}

FText UDiscipleMessage::GetMarry(FText& name1, FText& name2, int32 year) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(year), FStringFormatArg(name1.ToString()),
	FStringFormatArg(name2.ToString()) };
	str = Read(21);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::GetDivorce(FText& name1, FText& name2, int32 year) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(year), FStringFormatArg(name1.ToString()),
	FStringFormatArg(name2.ToString()) };
	str = Read(22);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

FText UDiscipleMessage::GetAfterBattle(FDisciple& dis, TArray<int32> attribute) {
	FString str = "";
	TArray<FStringFormatArg> args = { FStringFormatArg(dis.surname.ToString()), 
		FStringFormatArg(dis.name.ToString()),  FStringFormatArg(attribute[0]),
		FStringFormatArg(attribute[1]), FStringFormatArg(attribute[2]) };

	str = Read(23);
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

