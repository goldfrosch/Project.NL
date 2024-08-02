#include "CombatManager.h"

#include "WeaponManager.h"
#include "ProjectNL/DataTable/CombatAnimationData.h"

UAnimMontage* UCombatManager::GetUnEquipAnimation(
	const FDataTableRowHandle CombatDT
	, const EPlayerCombatWeaponState CurrentEquipStatus)
{
	const FString UnEquipAnimRowName =
		FEnumHelper::GetClassEnumKeyAsString(CurrentEquipStatus) + "UnEquipAnim";

	if (const FCombatAnimationData* UnEquipAnim = CombatDT.DataTable->FindRow<
		FCombatAnimationData>(*UnEquipAnimRowName, ""))
	{
		return UnEquipAnim->AnimGroup.Top();
	}
	return nullptr;
}

// TODO: 추후 위의 GetUnEquipAnimation과 합치기
UAnimMontage* UCombatManager::GetEquipAnimation(
	const FDataTableRowHandle CombatDT
	, const EPlayerCombatWeaponState CurrentEquipStatus)
{
	const FString UnEquipAnimRowName = FEnumHelper::GetClassEnumKeyAsString(
		CurrentEquipStatus) + "EquipAnim";
	if (const FCombatAnimationData* UnEquipAnim = CombatDT.DataTable->FindRow<
		FCombatAnimationData>(*UnEquipAnimRowName, ""))
	{
		return UnEquipAnim->AnimGroup.Top();
	}
	return nullptr;
}

TArray<UAnimMontage*> UCombatManager::GetAttackAnimation(
	const FDataTableRowHandle CombatDT
	, const EPlayerCombatWeaponState CurrentEquipStatus)
{
	const FString AnimName = FEnumHelper::GetClassEnumKeyAsString(
		CurrentEquipStatus) + "AttackAnim";

	if (const FCombatAnimationData* Animation = CombatDT.DataTable->FindRow<
		FCombatAnimationData>(*AnimName, ""))
	{
		return Animation->AnimGroup;
	}

	return TArray<UAnimMontage*>();
}
