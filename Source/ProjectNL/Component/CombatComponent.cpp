#include "CombatComponent.h"

#include "ProjectNL/Animation/Characters/ComboAttack/ComboAttackNotifyState.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::SetAttackMontages(TArray<UAnimMontage*> Montages)
{
	AttackMontages.SetNum(0);
	AttackMontages.Append(Montages);
	MaxCombo = AttackMontages.Num();
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
		if (const TObjectPtr<UComboAttackNotifyState> ComboAttackNotifyState =
			UAnimNotifyManager::FindNotifyStateByClass<UComboAttackNotifyState>(AttackMontages[ComboIndex])
		)
		{
			ComboAttackNotifyState->OnNotifiedBegin.AddDynamic(this, &UCombatComponent::OnComboBegin);
			ComboAttackNotifyState->OnNotifiedTick.AddDynamic(this, &UCombatComponent::SetComboDisable);
			ComboAttackNotifyState->OnNotifiedEnd.AddDynamic(this, &UCombatComponent::OnComboEnd);

			OnNotifiedComboAttackInit.Broadcast(AttackMontages[ComboIndex]);
		}
	}	
}
