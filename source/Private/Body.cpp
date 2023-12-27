// Fill out your copyright notice in the Description page of Project Settings.


#include "Body.h"

FOrgan::FOrgan() {
	id = 0;
	value = 0;
	price = 0;
	newValue = 0;
	sellPrice = 0;
	affix.Empty();
}

void FOrgan::Create(EOrganType oType) {
	int32 min = value * 0.9;
	int32 max = value * 1.1;
	newValue = FMath::RandRange(min, max);
	min = price * 0.9;
	max = price * 1.1;
	sellPrice = FMath::RandRange(min, max);
	type = oType;
	affix.Empty();
	for (int32 i = 0; i < 3; i++) {
		FEquipAffix temp;
		temp.OrganAffix();
		affix.Emplace(temp);
	}
}

int32 FOrgan::GetHealth() {
	int32 health = 0;
	health += GetValue(EAffix::Health);
	switch (type)
	{
	case EOrganType::Hand:
		break;
	case EOrganType::Foot:
		break;
	case EOrganType::Heart:
		health += newValue;
		break;
	case EOrganType::Lung:
		break;
	case EOrganType::Kidney:
		break;
	default:
		break;
	}
	return health;
}

int32 FOrgan::GetDamage() {
	int32 damage = 0;
	damage += GetValue(EAffix::Attack);
	switch (type)
	{
	case EOrganType::Hand:
		damage += newValue;
		break;
	case EOrganType::Foot:
		break;
	case EOrganType::Heart:
		break;
	case EOrganType::Lung:
		break;
	case EOrganType::Kidney:
		break;
	default:
		break;
	}
	return damage;
}

int32 FOrgan::GetDefense() {
	int32 defense = 0;
	defense += GetValue(EAffix::Defense);
	switch (type)
	{
	case EOrganType::Hand:
		break;
	case EOrganType::Foot:
		defense += newValue;
		break;
	case EOrganType::Heart:
		break;
	case EOrganType::Lung:
		defense += newValue;
		break;
	case EOrganType::Kidney:
		defense += newValue;
		break;
	default:
		break;
	}
	return defense;
}

int32 FOrgan::GetValue(EAffix affixType) {
	int32 temp = 0;
	for (auto& i : affix)
		if (i.affix == affixType)
			temp += i.value;

	return temp;
}

FBody::FBody() {

}

int32 FBody::GetHealth() {
	int32 value = 0;
	value += hand.GetHealth();
	value += foot.GetHealth();
	value += heart.GetHealth();
	value += lung.GetHealth();
	value += kidney.GetHealth();
	return value;
}

int32 FBody::GetDamage() {
	int32 value = 0;
	value += hand.GetDamage();
	value += foot.GetDamage();
	value += heart.GetDamage();
	value += lung.GetDamage();
	value += kidney.GetDamage();
	return value;
}

int32 FBody::GetDefense() {
	int32 value = 0;
	value += hand.GetDefense();
	value += foot.GetDefense();
	value += heart.GetDefense();
	value += lung.GetDefense();
	value += kidney.GetDefense();
	return value;
}
