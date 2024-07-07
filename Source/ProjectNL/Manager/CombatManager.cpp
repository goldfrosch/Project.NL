// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"

#include "GameFramework/Character.h"
#include "ProjectNL/DataTable/CombatAnimationData.h"
#include "ProjectNL/Weapon/WeaponBase.h"

void UCombatManager::UnSheathCharacterWeapon(const ACharacter* Character, AWeaponBase* Weapon, const bool IsMain)
{
	if (!IsValid(Character) || !IsValid(Weapon)) return;
	
	Weapon->AttachToComponent(
		Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
			IsMain ? "weapon_r" : "weapon_l"
		);
}

EHandEquipStatus UCombatManager::GetCharacterEquipStatus(const AWeaponBase* MainWeapon, const AWeaponBase* SubWeapon)
{
	if (!IsValid(MainWeapon) && !IsValid(SubWeapon)) return Empty;
	if (!IsValid(MainWeapon)) return OnlySub;
	if (!IsValid(SubWeapon)) return OnlyMain;
	
	if (MainWeapon->WeaponType != EUWeaponType::ET_None)
	{
		if (SubWeapon->WeaponType != EUWeaponType::ET_None && SubWeapon->WeaponType != EUWeaponType::ET_Shield)
		{
			return Dual;
		}
		return OnlyMain;
	}
	if (SubWeapon->WeaponType != EUWeaponType::ET_None && SubWeapon->WeaponType != EUWeaponType::ET_Shield)
	{
		return OnlySub;
	}
	return Empty;
}


UAnimMontage* UCombatManager::GetUnSheathingAnimation(
	FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon)
{
	const EHandEquipStatus CurrentEquipStatus = GetCharacterEquipStatus(MainWeapon, SubWeapon);

	FName UnSheathAnimRowName;

	switch (CurrentEquipStatus)
	{
		case Empty:
			UnSheathAnimRowName = "Empty";
			break;
		case OnlyMain:
			UnSheathAnimRowName = "OnlyMainUnSheathAnim";
			break;
		case OnlySub:
			UnSheathAnimRowName = "OnlySubUnSheathAnim";
			break;
		case Dual:
			UnSheathAnimRowName = "DualUnSheathAnim";
			break;
	}

	UE_LOG(LogTemp, Display, TEXT("%s"), *UnSheathAnimRowName.ToString());
	
	if (const FCombatAnimationData* UnSheathingAnim = CombatDT.DataTable->FindRow<FCombatAnimationData>(UnSheathAnimRowName, ""))
	{
		return UnSheathingAnim->AnimGroup.Top();
	}
	return nullptr;
}

