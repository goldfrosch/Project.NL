// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"

#include "WeaponManager.h"
#include "ProjectNL/DataTable/CombatAnimationData.h"

UAnimMontage* UCombatManager::GetUnSheathingAnimation(
	FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon)
{
	const EHandEquipStatus CurrentEquipStatus = UWeaponManager::GetCharacterEquipStatus(MainWeapon, SubWeapon);

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
	
	if (const FCombatAnimationData* UnSheathingAnim = CombatDT.DataTable->FindRow<FCombatAnimationData>(UnSheathAnimRowName, ""))
	{
		return UnSheathingAnim->AnimGroup.Top();
	}
	return nullptr;
}

// TODO: 추후 위의 GetUnSheathingAnimation과 합치기
UAnimMontage* UCombatManager::GetSheathingAnimation(
	FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon)
{
	const EHandEquipStatus CurrentEquipStatus = UWeaponManager::GetCharacterEquipStatus(MainWeapon, SubWeapon);

	FName UnSheathAnimRowName;

	switch (CurrentEquipStatus)
	{
	case Empty:
		UnSheathAnimRowName = "Empty";
		break;
	case OnlyMain:
		UnSheathAnimRowName = "OnlyMainSheathAnim";
		break;
	case OnlySub:
		UnSheathAnimRowName = "OnlySubSheathAnim";
		break;
	case Dual:
		UnSheathAnimRowName = "DualSheathAnim";
		break;
	}
	
	if (const FCombatAnimationData* UnSheathingAnim = CombatDT.DataTable->FindRow<FCombatAnimationData>(UnSheathAnimRowName, ""))
	{
		return UnSheathingAnim->AnimGroup.Top();
	}
	return nullptr;
}

