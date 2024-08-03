#include "CombatComponent.h"

#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/CombatManager.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::UpdateCombatStatus()
{
	SetPlayerCombatWeaponState(
		FStateHelper::GetCharacterWeaponState(GetMainWeapon(), GetSubWeapon()));
	EquipAnim = UCombatManager::GetEquipAnimation(
		CombatAnimData, GetPlayerCombatWeaponState());
	UnEquipAnim = UCombatManager::GetUnEquipAnimation(
		CombatAnimData, GetPlayerCombatWeaponState());
	DoubleJumpAnim = UCombatManager::GetDoubleJumpAnimation(
		CombatAnimData, GetPlayerCombatWeaponState());
}
