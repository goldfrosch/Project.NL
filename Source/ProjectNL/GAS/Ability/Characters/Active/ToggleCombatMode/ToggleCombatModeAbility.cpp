#include "ToggleCombatModeAbility.h"

#include "AbilitySystemComponent.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/GAS/Ability/Utility/PlayMontageWithEvent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Manager/CombatManager.h"
#include "AnimNotify/GrabWeaponNotify.h"
#include "AnimNotify/PutWeaponNotify.h"
#include "AnimNotify/SwapTwoHandWeaponNotify.h"

UToggleCombatModeAbility::UToggleCombatModeAbility(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UToggleCombatModeAbility::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayTagContainer* SourceTags
	, const FGameplayTagContainer* TargetTags
	, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags
																, OptionalRelevantTags))
	{
		return false;
	}
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		ActorInfo->AvatarActor.Get()))
	{
		if (IsValid(OwnerCharacter->GetAbilitySystemComponent()))
		{
			return FStateHelper::IsPlayerIdle(
				OwnerCharacter->GetAbilitySystemComponent());
		}
	}

	return false;
}

void UToggleCombatModeAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo
	, const FGameplayEventData* TriggerEventData)
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		ActorInfo->AvatarActor.Get()))
	{
		HandleToggleCombat();
		if (UCombatManager::IsCharacterCombat(
			OwnerCharacter->GetAbilitySystemComponent()))
		{
			SetCurrentMontage(OwnerCharacter->CombatComponent->GetUnEquipAnim());
			// 애니메이션 Notify 추가
			PutWeaponNotify = UAnimNotifyManager::FindNotifyByClass<UPutWeaponNotify>(
				GetCurrentMontage());
			if (IsValid(PutWeaponNotify))
			{
				PutWeaponNotify->OnNotified.AddDynamic(this, &ThisClass::HandleUnEquip);
			}
		}
		else
		{
			SetCurrentMontage(OwnerCharacter->CombatComponent->GetEquipAnim());
			// 애니메이션 Notify 추가
			GrabWeaponNotify = UAnimNotifyManager::FindNotifyByClass<
				UGrabWeaponNotify>(GetCurrentMontage());
			if (IsValid(GrabWeaponNotify))
			{
				GrabWeaponNotify->OnNotified.AddDynamic(this, &ThisClass::HandleEquip);
			}

			SwapTwoHandWeaponNotify = UAnimNotifyManager::FindNotifyByClass<
				USwapTwoHandWeaponNotify>(GetCurrentMontage());
			if (IsValid(SwapTwoHandWeaponNotify))
			{
				SwapTwoHandWeaponNotify->OnNotified.AddDynamic(
					this, &ThisClass::HandleSwapTwoHandWeapon);
			}
		}

		UPlayMontageWithEvent* Task = UPlayMontageWithEvent::InitialEvent(
			this, NAME_None, GetCurrentMontage(), FGameplayTagContainer());

		Task->OnCompleted.AddDynamic(this, &ThisClass::HandleToggleCombatEnd);
		Task->OnCancelled.AddDynamic(this, &ThisClass::HandleCancelAbilityTask);

		Task->ReadyForActivation();
	}
}

void UToggleCombatModeAbility::HandleUnEquip()
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
		if (IsValid(CombatComponent->GetMainWeapon()))
		{
			CombatComponent->GetMainWeapon()->UnEquipCharacterWeapon(true);
		}
		if (IsValid(CombatComponent->GetSubWeapon()))
		{
			CombatComponent->GetSubWeapon()->UnEquipCharacterWeapon(false);
		}
		GetAbilitySystemComponentFromActorInfo()->SetLooseGameplayTagCount(
			NlGameplayTags::Status_Combat, 0);
		FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																		, NlGameplayTags::State_Player_UnEquip
																		, NlGameplayTags::State_Player_Idle);
	}
}

void UToggleCombatModeAbility::HandleEquip()
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
		if (IsValid(CombatComponent->GetMainWeapon()))
		{
			CombatComponent->GetMainWeapon()->EquipCharacterWeapon(
				Cast<ACharacter>(GetAvatarActorFromActorInfo()), true);
		}
		if (IsValid(CombatComponent->GetSubWeapon()))
		{
			CombatComponent->GetSubWeapon()->EquipCharacterWeapon(
				Cast<ACharacter>(GetAvatarActorFromActorInfo()), false);
		}

		GetAbilitySystemComponentFromActorInfo()->SetLooseGameplayTagCount(
			NlGameplayTags::Status_Combat, 1);
		FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																		, NlGameplayTags::State_Player_Equip
																		, NlGameplayTags::State_Player_Idle);
	}
}

void UToggleCombatModeAbility::HandleSwapTwoHandWeapon()
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
		if (IsValid(CombatComponent->GetMainWeapon()))
		{
			CombatComponent->GetMainWeapon()->SwapTwoHandWeapon();
		}
	}
}


void UToggleCombatModeAbility::HandleToggleCombat()
{
	const bool IsCombat = UCombatManager::IsCharacterCombat(
		GetAbilitySystemComponentFromActorInfo());
	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, NlGameplayTags::State_Player_Idle
																	, IsCombat
																			? NlGameplayTags::State_Player_UnEquip
																			: NlGameplayTags::State_Player_Equip);
}

void UToggleCombatModeAbility::HandleToggleCombatEnd(
	FGameplayTag EventTag, FGameplayEventData EventData)
{
	ClearDelegate();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
						, false);
}

void UToggleCombatModeAbility::HandleCancelAbilityTask(FGameplayTag EventTag
	, FGameplayEventData EventData)
{
	const bool IsCombat = UCombatManager::IsCharacterCombat(
		GetAbilitySystemComponentFromActorInfo());

	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, IsCombat
																			? NlGameplayTags::State_Player_Equip
																			: NlGameplayTags::State_Player_UnEquip
																	, NlGameplayTags::State_Player_Idle);
}

void UToggleCombatModeAbility::ClearDelegate()
{
	if (PutWeaponNotify)
	{
		PutWeaponNotify->OnNotified.RemoveAll(this);
	}
	if (GrabWeaponNotify)
	{
		GrabWeaponNotify->OnNotified.RemoveAll(this);
	}
	if (SwapTwoHandWeaponNotify)
	{
		SwapTwoHandWeaponNotify->OnNotified.RemoveAll(this);
	}
}
