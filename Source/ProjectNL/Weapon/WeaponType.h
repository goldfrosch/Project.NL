// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponType.generated.h"

UENUM(BlueprintType)
enum class EUEquippedHandType : uint8
{
	ET_None			UMETA(DisplayName = "None"),
	ET_OneHand		UMETA(DisplayName = "OneHand"),
	ET_TwoHand		UMETA(DisplayName = "TwoHand"),
};

UENUM(BlueprintType)
enum class EUWeaponType : uint8
{
	ET_None					UMETA(DisplayName = "None"),
	ET_Axe			UMETA(DisplayName = "Axe"),
	ET_Sword			UMETA(DisplayName = "Sword"),
	ET_Shield		UMETA(DisplayName = "Shield"),
	ET_Spear			UMETA(DisplayName = "Spear"),
};
