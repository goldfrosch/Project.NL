// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponManager.generated.h"

class AWeaponBase;

UENUM()
enum EHandEquipStatus
{
	Empty,
	OnlyMain,
	OnlySub,
	Dual,
};

UCLASS()
class PROJECTNL_API UWeaponManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	static void UnSheathCharacterWeapon(const ACharacter* Character, AWeaponBase* Weapon, const bool IsMain);
	
	UFUNCTION()
	static void SheathCharacterWeapon(const ACharacter* Character, AWeaponBase* Weapon, const bool IsMain);
	
	UFUNCTION()
	static void StartSheathCharacterWeapon(AWeaponBase* Weapon);

	static EHandEquipStatus GetCharacterEquipStatus(const AWeaponBase* MainWeapon, const AWeaponBase* SubWeapon);
};
