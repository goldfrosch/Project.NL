// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Weapon/WeaponBase.h"
#include "UObject/Object.h"
#include "WeaponManager.generated.h"

enum class EUWeaponType : uint8;
class AWeaponBase;

UCLASS()
class PROJECTNL_API UWeaponManager : public UObject
{
	GENERATED_BODY()

public:
	static EHandEquipStatus GetCharacterEquipStatus(
		AWeaponBase* MainWeapon, AWeaponBase* SubWeapon);
};
