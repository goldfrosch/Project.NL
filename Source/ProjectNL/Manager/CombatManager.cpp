#include "CombatManager.h"

#include "AbilitySystemComponent.h"
#include "ProjectNL/DataTable/CombatAnimationData.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"

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
	if (const FCombatAnimationData* EquipAnim = CombatDT.DataTable->FindRow<
		FCombatAnimationData>(*UnEquipAnimRowName, ""))
	{
		return EquipAnim->AnimGroup.Top();
	}
	return nullptr;
}

UAnimMontage* UCombatManager::GetDoubleJumpAnimation(
	const FDataTableRowHandle CombatDT
	, const EPlayerCombatWeaponState CurrentEquipStatus)
{
	const FString UnEquipAnimRowName = FEnumHelper::GetClassEnumKeyAsString(
		CurrentEquipStatus) + "DoubleJumpAnim";
	if (const FCombatAnimationData* EquipAnim = CombatDT.DataTable->FindRow<
		FCombatAnimationData>(*UnEquipAnimRowName, ""))
	{
		return EquipAnim->AnimGroup.Top();
	}
	return nullptr;
}

UAnimMontage* UCombatManager::GetDamagedAnimation(
	const FDataTableRowHandle CombatDT, FVector DamagedActorVector
	, FRotator DamagedActorRotator)
{
	EDamagedHeight Height = EDamagedHeight::Middle;
	EDamagedDirection Direction = EDamagedDirection::Front;
	// 임의로 높이 50 이상이 되는 경우 높게 설정함
	// 추후 Actor 자체의 높이를 가져와서 처리하는 것이 가장 나아보임
	if (DamagedActorVector.Z > 30)
	{
		Height = EDamagedHeight::High;
	}
	else if (DamagedActorVector.Z < -30)
	{
		Height = EDamagedHeight::Low;
	}

	if (DamagedActorRotator.Yaw > 45 && DamagedActorRotator.Yaw <= 135)
	{
		Direction = EDamagedDirection::Right;
	}
	else if (DamagedActorRotator.Yaw >= -135 && DamagedActorRotator.Yaw < -45)
	{
		Direction = EDamagedDirection::Left;
	}
	else if ((DamagedActorRotator.Yaw > 135 && DamagedActorRotator.Yaw <= 180) ||
		(DamagedActorRotator.Yaw >= -180 && DamagedActorRotator.Yaw < -135))
	{
		Direction = EDamagedDirection::Back;
	}

	const FString AnimTitle = "Damage" +
		FEnumHelper::GetClassEnumKeyAsString(Height) +
		FEnumHelper::GetClassEnumKeyAsString(Direction);

	if (const FCombatAnimationData* AnimData = CombatDT.DataTable->FindRow<
		FCombatAnimationData>(*AnimTitle, ""))
	{
		return AnimData->AnimGroup.Top();
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

bool UCombatManager::IsCharacterCombat(const UAbilitySystemComponent* Ability)
{
	if (!IsValid(Ability))
	{
		return false;
	}
	return Ability->HasMatchingGameplayTag(NlGameplayTags::Status_Combat);
}
