// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.generated.h"

UENUM(BlueprintType)
enum class EUWeaponType : uint8
{
	ET_None			UMETA(DisplayName = "None"),
	ET_OneHandSword	UMETA(DisplayName = "OneHandSword"),
	ET_TwoHandAxe 	UMETA(DisplayName = "TwoHandAxe"),
	ET_TwoHandSpear UMETA(DisplayName = "TwoHandSpear")
};
