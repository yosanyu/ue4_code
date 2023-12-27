// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Law.h"
#include "Elixirs.h"
#include "SpiritBeast.h"
#include "Shop.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FShop {

	GENERATED_BODY()

	FShop();

	// �C�~��s�c�⪺�f�� �ǤJ�|������\�k�����
	void UpdateGood(TArray<FLaw> noGet);

	// ��s�c�⪺�˳�
	void UpdateEquipments();

	// ��s�c�⪺�\�k �ǤJ�|������\�k�����
	void UpdateLaws(TArray<FLaw>& noGet);

	// �Ӧ�c�⪺�˳�
	UPROPERTY(BlueprintReadWrite)
	TArray<FEquipment> equips;

	// �Ӧ�c�⪺�\�k
	UPROPERTY(BlueprintReadWrite)
	TArray<FLaw> laws;

	// �Ӧ�c�⪺�F�~
	UPROPERTY(BlueprintReadWrite)
	TArray<FSpiritBeast> spiritBeasts;

	//�Ӧ��s����
	UPROPERTY(BlueprintReadWrite)
	int32 updateTimes = 3;

	// �̤l�ۦ����� �C�ۦ�40��̤l���ɰ����̤l����o���v �̰�����4��
	UPROPERTY(BlueprintReadWrite)
	int32 disTimes = 0;
};


USTRUCT(BlueprintType)
struct FSectSystem {

	GENERATED_BODY()

	FSectSystem();

	// ���L�����e§������
	UPROPERTY(BlueprintReadWrite)
	int32 giftTimes;

	// ���L��������������
	UPROPERTY(BlueprintReadWrite)
	int32 alienateTimes;

	// ���L�����������Ҫ�����
	UPROPERTY(BlueprintReadWrite)
	int32 exploreTimes;

	// ���L��������������
	UPROPERTY(BlueprintReadWrite)
	int32 attackTimes;

	// �i���������
	UPROPERTY(BlueprintReadWrite)
	int32 lottery;
};

USTRUCT(BlueprintType)
struct FBuilding : public FTableRowBase {

	GENERATED_BODY()

	FBuilding();

	// �_�ݫؿv��id
	UPROPERTY(BlueprintReadWrite)
	int32 id;

	// �_�ݫؿv���W��
	UPROPERTY(BlueprintReadWrite)
	FText name;

	// �_�ݫؿv���ĪG
	UPROPERTY(BlueprintReadWrite)
	FText effect;

	// �_�ݫؿv�[���ƭ�
	UPROPERTY(BlueprintReadWrite)
	int32 value;

	// �_�ݫؿv���سy����
	UPROPERTY(BlueprintReadWrite)
	int32 price;

	// �_�ݫؿv�O�_�w�Q�سy
	UPROPERTY(BlueprintReadWrite)
	bool hasBuilded;

	// �_�ݫؿv�ĪG����
	UPROPERTY(BlueprintReadWrite)
	ESectValue type;

};