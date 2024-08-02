#include "CombatAComponent.h"

#include "ProjectNL/Animation/Characters/Attack/ComboAttackNotifyState.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Manager/CombatManager.h"


UCombatAComponent::UCombatAComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatAComponent::SetAttackMontages(TArray<UAnimMontage*> Montages)
{
	AttackMontages.SetNum(0);
	AttackMontages.Append(Montages);
	MaxCombo = AttackMontages.Num();
	for (UAnimMontage* AttackAnim : AttackMontages)
	{
		if (const TObjectPtr<UComboAttackNotifyState> ComboAttackNotifyState =
			UAnimNotifyManager::FindNotifyStateByClass<UComboAttackNotifyState>(
				AttackAnim))
		{
			ComboAttackNotifyState->OnNotifiedBegin.AddDynamic(
				this, &UCombatAComponent::OnComboBegin);
			ComboAttackNotifyState->OnNotifiedTick.AddDynamic(
				this, &UCombatAComponent::SetComboDisable);
			ComboAttackNotifyState->OnNotifiedEnd.AddDynamic(
				this, &UCombatAComponent::OnComboEnd);
		}
	}
}


void UCombatAComponent::OnComboBegin()
{
	OnNotifiedComboAttackStart.Broadcast();
}

void UCombatAComponent::OnComboEnd()
{
	ComboIndex = ComboIndex == MaxCombo - 1 ? 0 : ComboIndex + 1;
	IsNextCombo = true;
	OnNotifiedComboAttackEnd.Broadcast();
}


void UCombatAComponent::SetComboDisable()
{
	IsNextCombo = false;
}

void UCombatAComponent::ComboAttack()
{
	if (!AttackMontages.IsEmpty())
	{
		OnNotifiedComboAttackInit.Broadcast(AttackMontages[ComboIndex]);
	}
}

void UCombatAComponent::UpdateWeaponData()
{
	// EquipAnimMontage = UCombatManager::GetEquipAnimation(
	// 	CombatAnimData, MainWeapon, SubWeapon);
	// UnEquipAnimMontage = UCombatManager::GetUnEquipAnimation(
	// 	CombatAnimData, MainWeapon, SubWeapon);
	//
	// const TArray<UAnimMontage*> AttackMontage =
	// 	UCombatManager::GetAttackAnimation(CombatAnimData, MainWeapon, SubWeapon);
	// SetAttackMontages(AttackMontage);
}
