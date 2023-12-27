// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sect.h"
#include "DiscipleEvent.generated.h"

/**
 * 
 */
UCLASS()
class DEVELOPVER1_API UDiscipleEvent : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	static void StartEvent(USect* sect);

	static void DoEvent(USect* sect, int32& index);

	static void GetEquipmentEvent(USect* sect, int32& index);
	
	static void DeathEvent(USect* sect, int32& index);

	static void WifeEvent(USect* sect, int32& index);

	static void DivorceEvent(USect* sect, int32& index);

	static void MarryEvent(USect* sect, int32& index);

	static void SexyEvent(USect* sect, int32& index);

	static void LifeTreasureEvent(USect* sect, int32& index);

	static void StarSoulEvent(USect* sect, int32& index);

	static void EatEilxir(USect* sect, int32& index);
};

class DEVELOPVER1_API UEventMessage {
public:
	static FText GetEqupment(const FDisciple& dis, const FEquipment& e, int32 index);

	static FText GetDeath(const FDisciple& dis, int32 index);

	static FText GetWifeEvent(const FDisciple& dis, int32 index);

	static FText GetLifeTreasure(FDisciple& dis, int32 index, FText name);

	static FText GetStarSoul(FDisciple& dis, int32 index, FText name);
};