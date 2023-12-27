// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleBattle.h"
#include "HandleDisciple.h"
#include "HandleSpiritBeast.h"

int32 UHandleBattle::GetPlayerDamage(USect* sect, const TArray<UEnemySect*>& eSect) {
	int32 damage = 0;
	for (auto& i : sect->disciples)
		damage += UHandleDisciple::GetDamage(i);

	if (sect->elders[0].CheckSkill())
		damage *= 1.5;

	for (auto& i : sect->spiritBeasts)
		damage += UHandleSpiritBeast::GetAttack(i);

	damage += sect->attack;
	damage += gDisAttack;

	damage *= (gSectABuff + 1.0);

	for (auto& i : eSect) {
		if (i->allianced) {
			for(int32 n=0;n<10;n++)
				damage += UHandleDisciple::GetDamage(i->disciples[n]);
		}
	}

	return damage;
}

int32 UHandleBattle::GetPlayerHealth(USect* sect, const TArray<UEnemySect*>& eSect) {
	int32 health = 0;
	for (auto& i : sect->disciples)
		health += UHandleDisciple::GetHealth(i);

	if (sect->elders[1].CheckSkill())
		health *= 1.5;

	for (auto& i : sect->spiritBeasts)
		health += UHandleSpiritBeast::GetHealth(i);

	health += sect->health;
	health += gDisHealth;

	health *= (gSectHBuff + 1.0);
	for (auto& i : eSect) {
		if (i->allianced) {
			for (int32 n = 0; n < 10; n++)
				health += UHandleDisciple::GetHealth(i->disciples[n]);
		}
	}

	return health;
}

int32 UHandleBattle::GetPlayerDefense(USect* sect, const TArray<UEnemySect*>& eSect) {
	int32 defense = 0;
	for (auto& i : sect->disciples)
		defense += UHandleDisciple::GetDefense(i);

	if (sect->elders[2].CheckSkill())
		defense *= 1.5;

	for (auto& i : sect->spiritBeasts)
		defense += UHandleSpiritBeast::GetDefense(i);

	defense += sect->defense;
	defense += gDisDefense;
	defense *= (gSectDBuff + 1.0);

	for (auto& i : eSect) {
		if (i->allianced) {
			for (int32 n = 0; n < 10; n++)
				defense += UHandleDisciple::GetDefense(i->disciples[n]);
		}
	}

	return defense;
}

int32 UHandleBattle::GetESectDamage(UEnemySect* sect) {
	int32 damage = 0;
	for (auto& i : sect->disciples)
		damage += UHandleDisciple::GetDamage(i);
	return damage;
}

int32 UHandleBattle::GetESectHealth(UEnemySect* sect) {
	int32 health = 0;
	for (auto& i : sect->disciples)
		health += UHandleDisciple::GetHealth(i);
	return health;
}

int32 UHandleBattle::GetESectDefense(UEnemySect* sect) {
	int32 defense = 0;
	for (auto& i : sect->disciples)
		defense += UHandleDisciple::GetDefense(i);
	return defense;
}

TArray<int32> UHandleBattle::TwoDisBattle(FDisciple player, FDisciple enemy, int32 playerH, int32 enemyH) {
	int32 pDamage = player.GetDamage();

	if (pDamage - UHandleDisciple::GetDefense(enemy) * 1.2 < 500) {
		enemyH -= 500;
	}
	else {
		enemyH = enemyH - (pDamage - UHandleDisciple::GetDefense(enemy) * 1.2);
	}
	int32 eDamage = enemy.GetDamage();
	if (eDamage - UHandleDisciple::GetDefense(player) * 1.2 < 500) {
		playerH -= 500;
	}
	else {
		playerH = playerH - (eDamage - UHandleDisciple::GetDefense(player) * 1.2);
	}
	
	TArray<int32> remaining = { playerH, enemyH };
	return remaining;
}

TArray<int32> UHandleBattle::TeamBattle(UMyGameInstance* instance, TArray<int32> h, TArray<float> p) {
	TArray<int32> damages  = { 0, 0 };
	TArray<int32> defenses = { 0, 0 };

	// 計算玩家屬性
	USect* sect = instance->sect;
	SetPlayerDamage(sect, damages[0], p[0], instance->enemys);
	// 防禦戰啟用防禦塔
	if (instance->eSectMode == 2)
		UseTower(sect, damages[0]);

	SetPlayerDefense(sect, defenses[0], p[0], instance->enemys);

	float ignoreDefense = 1.0 - gIgnoreDefense; // 無視防禦
	float reduceDamage = 1.0 - gReduceDamage;	// 減少受到的傷害
	UEnemySect* enemy = instance->enemys[instance->enemyIndex];
	SetEnemySectDamage(enemy, damages[1], p[1]);
	SetEnemySectDefense(enemy, defenses[1], p[1]);
	defenses[1] *= ignoreDefense;	// 套用無視防禦
	damages[1] *= reduceDamage;		// 套用減傷

	// 滅門戰敵人屬性*1.4
	if (instance->eSectMode == 1) {
		damages[1] *= 1.4;
		defenses[1] *= 1.4;
	}

	// 玩家受到傷害
	if (damages[1] - defenses[0] > 0) {
		h[0] = h[0] - (damages[1] - defenses[0]);
		damages[1] -= defenses[0];
	}
	else
		damages[1] = 0;
	
	// 敵人受到傷害
	if (damages[0] - defenses[1] > 0) {
		h[1] = h[1] - (damages[0] - defenses[1]);
		damages[0] -= defenses[1];
	}
	else
		damages[0] = 0;

	for (auto& i : h)
		if (i < 0)
			i = 0;

	TArray<int32> returns = { h[0], h[1], damages[0], damages[1] };

	return returns;
}

TArray<float> UHandleBattle::GetRemaining(USect* sect, UEnemySect* enemy, int32 PH, int32 EH, const TArray<UEnemySect*>& eSect) {
	float p = (float(PH)) / (float(GetPlayerHealth(sect, eSect)));
	float e = (float(EH)) / (float(GetESectHealth(enemy)));
	return TArray<float>({p, e});
}

TArray<int32> UHandleBattle::AttackDemon(UMyGameInstance* instance, TArray<int32> h, TArray<float> p) {
	TArray<int32> damages = { 0, 0 };
	TArray<int32> defenses = { 0, 0 };

	// 計算玩家屬性
	USect* sect = instance->sect;
	SetPlayerDamage(sect, damages[0], p[0], instance->enemys);
	SetPlayerDefense(sect, defenses[0], p[0], instance->enemys);

	float ignoreDefense = 1.0 - gIgnoreDefense;
	FDemon demon = instance->demons[instance->demonIndex];
	damages[1] = demon.attack;
	defenses[1] = demon.defense;
	defenses[1] *= ignoreDefense;

	// 玩家受到傷害
	if (damages[1] - defenses[0] > 0) {
		h[0] = h[0] - (damages[1] - defenses[0]);
		damages[1] -= defenses[0];
	}
	else
		damages[1] = 0;

	// 敵人受到傷害
	if (damages[0] - defenses[1] > 0) {
		h[1] = h[1] - (damages[0] - defenses[1]);
		damages[0] -= defenses[1];
	}
	else
		damages[0] = 0;

	for (auto& i : h)
		if (i < 0)
			i = 0;

	TArray<int32> returns = { h[0], h[1], damages[0], damages[1] };

	return returns;
}

TArray<float> UHandleBattle::GetDRemaining(USect* sect, const FDemon& demon, int32 PH, int32 EH, const TArray<UEnemySect*>& eSect) {
	float p = (float(PH)) / (float(GetPlayerHealth(sect, eSect)));
	float e = (float(EH)) / (float(demon.health));
	return TArray<float>({ p, e });
}

int32 UHandleBattle::IsEnd(int32 PH, int32 EH) {
	// 0 還沒結束 1 平手 2贏 3輸
	int32 result = 0;
	if (PH > 0 && EH > 0)
		result = 0;
	else if (PH == 0 && EH == 0)
		result = 1;
	else if (EH == 0)
		result = 2;
	else if (PH == 0)
		result = 3;

	return result;
}

bool UHandleBattle::HasEnemy(UMyGameInstance* instance) {
	// 30
	if (GetNowYear() > 30) {
		TArray<int32> indexs;
		TArray<UEnemySect*> enemys = instance->enemys;
		for (int32 i = 0; i < enemys.Num(); i++)
			indexs.Add(i);

		int random = FMath::RandRange(0, indexs.Num() - 1);

		int32 enemyAttackP = FMath::RandRange(1, 100);
		// 10
		if (enemyAttackP <= 10) {
			if (indexs.Num() == 0)
				return false;
			else {
				int32 index = indexs[random];
				instance->enemyIndex = index;
				if (instance->enemys[index]->allianced)
					instance->enemys[index]->allianced = false;
				return true;
			}

		}
	}
	return false;
}

int32 UHandleBattle::UseMissle(USect* sect, int32 used) {
	sect->defenseFacility.missleNum -= used;
	return used * sect->defenseFacility.missleAttack;
}

void UHandleBattle::OneClickGame(UMyGameInstance* instance) {
	USect* sect = instance->sect;
	if (sect->disciples.Num() < 5)
		return;
	for (auto& i : instance->enemys) {
		if (i->canCommunicate) {
			i->canCommunicate = false;
			i->AddFriendly(5);
			TArray<int32> indexs = sect->GetFiveDisIndex();
			for (auto& index : indexs) {
				TArray<int32> attribute;
				for (int32 n = 0; n < 3; n++) {
					int32 random = FMath::RandRange(30, 60);
					attribute.Add(random);
				}
				sect->disciples[index].health += attribute[0];
				sect->disciples[index].attack += attribute[1];
				sect->disciples[index].defense += attribute[2];
			}
		}
	}
}

void SetPlayerDamage(USect* sect, int32& damage, float percent, const TArray<UEnemySect*>& eSect) {
	for (auto& i : sect->disciples)
		damage += i.GetDamage();

	if (sect->elders[0].CheckSkill())
		damage *= 1.5;

	for (auto& i : sect->spiritBeasts)
		damage += UHandleSpiritBeast::GetAttack(i);

	damage += sect->attack;
	damage += gDisAttack;
	for (auto& i : eSect) {
		if (i->allianced) {
			for (int32 n = 0; n < 10; n++)
				damage += UHandleDisciple::GetDamage(i->disciples[n]);
		}
	}
	damage *= percent;
}

void UseTower(USect* sect, int32& damage) {
	int32 n = sect->defenseFacility.towers.Num();
	for (int32 i = 0; i < n; i++) {
		if (i == 0) {
			if (FMath::RandRange(1, 100) <= 70)
				damage += sect->defenseFacility.towers[i].GetDamage();
		}
		damage += sect->defenseFacility.towers[i].GetDamage();
	}
}

void SetPlayerDefense(USect* sect, int32& defense, float percent, const TArray<UEnemySect*>& eSect) {
	for (auto& i : sect->disciples)
		defense += i.GetDefense();

	if (sect->elders[2].CheckSkill())
		defense *= 1.5;

	for (auto& i : sect->spiritBeasts)
		defense += UHandleSpiritBeast::GetDefense(i);

	defense += sect->defense;
	defense += gDisDefense;
	for (auto& i : eSect) {
		if (i->allianced) {
			for (int32 n = 0; n < 10; n++)
				defense += UHandleDisciple::GetDefense(i->disciples[n]);
		}
	}
	defense *= percent;
}

void SetEnemySectDamage(UEnemySect* sect, int32& damage, float percent) {
	for (auto& i : sect->disciples)
		damage += i.GetDamage();

	damage *= percent;
}

void SetEnemySectDefense(UEnemySect* sect, int32& defense, float percent) {
	for (auto& i : sect->disciples)
		defense += i.GetDefense();

	defense *= percent;
}
