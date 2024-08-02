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
	UFUNCTION()
	static void UnEquipCharacterWeapon(const ACharacter* Character
																		, AWeaponBase* Weapon, const bool IsMain);

	UFUNCTION()
	static void EquipCharacterWeapon(const ACharacter* Character
																	, AWeaponBase* Weapon, const bool IsMain);

	UFUNCTION()
	static void StartEquipCharacterWeapon(AWeaponBase* Weapon);

	static EHandEquipStatus GetCharacterEquipStatus(
		const AWeaponBase* MainWeapon, const AWeaponBase* SubWeapon);
};
