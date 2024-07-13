// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"

#include "WeaponManager.h"
#include "ProjectNL/DataTable/CombatAnimationData.h"
#include "ProjectNL/Helper/AnimHelper.h"

UAnimMontage* UCombatManager::GetUnSheathingAnimation(
	FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon)
{
	const EHandEquipStatus CurrentEquipStatus = UWeaponManager::GetCharacterEquipStatus(MainWeapon, SubWeapon);

	FName UnSheathAnimRowName;

	switch (CurrentEquipStatus)
	{
		case EHandEquipStatus::Empty:
			UnSheathAnimRowName = "Empty";
			break;
		case EHandEquipStatus::OnlyMain:
			UnSheathAnimRowName = "OnlyMainUnSheathAnim";
			break;
		case EHandEquipStatus::OnlySub:
			UnSheathAnimRowName = "OnlySubUnSheathAnim";
			break;
		case EHandEquipStatus::Dual:
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
	case EHandEquipStatus::Empty:
		UnSheathAnimRowName = "Empty";
		break;
	case EHandEquipStatus::OnlyMain:
		UnSheathAnimRowName = "OnlyMainSheathAnim";
		break;
	case EHandEquipStatus::OnlySub:
		UnSheathAnimRowName = "OnlySubSheathAnim";
		break;
	case EHandEquipStatus::Dual:
		UnSheathAnimRowName = "DualSheathAnim";
		break;
	}
	
	if (const FCombatAnimationData* UnSheathingAnim = CombatDT.DataTable->FindRow<FCombatAnimationData>(UnSheathAnimRowName, ""))
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
	
	UE_LOG(LogTemp, Display, TEXT("TEST: %s"), *AnimName);
	
	return nullptr;
}


