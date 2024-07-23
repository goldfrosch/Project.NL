#include "CombatComponent.h"

#include "ProjectNL/Animation/Characters/Attack/ComboAttackNotifyState.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Manager/CombatManager.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::SetAttackMontages(TArray<UAnimMontage*> Montages)
{
	AttackMontages.SetNum(0);
	AttackMontages.Append(Montages);
	MaxCombo = AttackMontages.Num();
	for (UAnimMontage* AttackAnim : AttackMontages)
	{
		if (const TObjectPtr<UComboAttackNotifyState> ComboAttackNotifyState =
    				UAnimNotifyManager::FindNotifyStateByClass<UComboAttackNotifyState>(AttackAnim)
    		)
    	{
    		ComboAttackNotifyState->OnNotifiedBegin.AddDynamic(this, &UCombatComponent::OnComboBegin);
    		ComboAttackNotifyState->OnNotifiedTick.AddDynamic(this, &UCombatComponent::SetComboDisable);
    		ComboAttackNotifyState->OnNotifiedEnd.AddDynamic(this, &UCombatComponent::OnComboEnd);
    	}	
	}
}


void UCombatComponent::OnComboBegin()
{
	OnNotifiedComboAttackStart.Broadcast();
}

void UCombatComponent::OnComboEnd()
{
	ComboIndex = ComboIndex == MaxCombo - 1 ? 0 : ComboIndex + 1;
	IsNextCombo = true;
	OnNotifiedComboAttackEnd.Broadcast();
}


void UCombatComponent::SetComboDisable()
{
	IsNextCombo = false;
}

void UCombatComponent::ComboAttack()
{
	if (!AttackMontages.IsEmpty())
	{
		OnNotifiedComboAttackInit.Broadcast(AttackMontages[ComboIndex]);
	}	
}

void UCombatComponent::UpdateWeaponData()
{
	SheathingAnimMontage = UCombatManager::GetSheathingAnimation(CombatAnimData, MainWeapon, SubWeapon);
	UnSheathingAnimMontage = UCombatManager::GetUnSheathingAnimation(CombatAnimData, MainWeapon, SubWeapon);
	
	const TArray<UAnimMontage*> AttackMontage = UCombatManager::GetAttackAnimation(
		CombatAnimData, MainWeapon, SubWeapon);
	SetAttackMontages(AttackMontage);
}