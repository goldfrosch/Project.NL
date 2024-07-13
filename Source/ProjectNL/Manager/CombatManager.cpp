// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"

#include "WeaponManager.h"
#include "ProjectNL/DataTable/CombatAnimationData.h"
#include "ProjectNL/Helper/AnimHelper.h"

UAnimMontage* UCombatManager::GetUnSheathingAnimation(
	FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon)
{
	const EHandEquipStatus CurrentEquipStatus = UWeaponManager::GetCharacterEquipStatus(MainWeapon, SubWeapon);

	const FString UnSheathAnimRowName = FEnumHelper::GetClassEnumKeyAsString(CurrentEquipStatus) + "UnSheathAnim";
	
	if (const FCombatAnimationData* UnSheathingAnim = CombatDT.DataTable->FindRow<FCombatAnimationData>(*UnSheathAnimRowName, ""))
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

	const FString UnSheathAnimRowName = FEnumHelper::GetClassEnumKeyAsString(CurrentEquipStatus) + "SheathAnim";
	
	if (const FCombatAnimationData* UnSheathingAnim = CombatDT.DataTable->FindRow<FCombatAnimationData>(*UnSheathAnimRowName, ""))
	{
		return UnSheathingAnim->AnimGroup.Top();
	}
	return nullptr;
}

UAnimMontage* UCombatManager::GetAttackAnimation(FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon)
{
	const FString AnimName = FAnimHelper::GetCombatAttackAnimation(CombatDT, MainWeapon, SubWeapon);

	if (const FCombatAnimationData* Animation = CombatDT.DataTable->FindRow<FCombatAnimationData>(*AnimName, ""))
	{
		return Animation->AnimGroup.Top();
	}
	
	return nullptr;
}


