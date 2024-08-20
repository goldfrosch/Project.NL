#include "CombatComponent.h"

#include "Net/UnrealNetwork.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/CombatManager.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MainWeapon = MainWeaponTemplate.GetDefaultObject();
	SubWeapon = SubWeaponTemplate.GetDefaultObject();
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, MainWeapon);
	DOREPLIFETIME(ThisClass, SubWeapon);
	DOREPLIFETIME(ThisClass, PlayerCombatWeaponState);
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType
																		, FActorComponentTickFunction*
																		ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugString(GetWorld(), FVector(0, 0, 100)
									, FEnumHelper::GetClassEnumKeyAsString(
										PlayerCombatWeaponState), GetOwner(), FColor::White
									, DeltaTime);
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
	ComboAttackAnim = UCombatManager::GetAttackAnimation(
		CombatAnimData, GetPlayerCombatWeaponState());
}
