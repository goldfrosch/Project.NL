#include "ToggleCombatModeAbility.h"

#include "AbilitySystemComponent.h"
#include "ProjectNL/Animation/Characters/Equip/GrabWeaponNotify.h"
#include "ProjectNL/Animation/Characters/Equip/PutWeaponNotify.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/GAS/Ability/Utility/PlayMontageWithEvent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Manager/CombatManager.h"
#include "ProjectNL/Manager/WeaponManager.h"

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
	return FStateHelper::IsPlayerIdle(GetAbilitySystemComponentFromActorInfo());
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
			GetAbilitySystemComponentFromActorInfo()))
		{
			SetCurrentMontage(OwnerCharacter->CombatComponent->GetUnEquipAnim());
			// 애니메이션 Notify 추가
			PutWeaponNotify = UAnimNotifyManager::FindNotifyByClass<UPutWeaponNotify>(
				GetCurrentMontage());
			if (IsValid(PutWeaponNotify))
			{
				PutWeaponNotify->OnNotified.AddDynamic(
					this, &UToggleCombatModeAbility::HandleUnEquip);
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
				GrabWeaponNotify->OnNotified.AddDynamic(
					this, &UToggleCombatModeAbility::HandleEquip);
			}
		}

		UPlayMontageWithEvent* Task = UPlayMontageWithEvent::InitialEvent(
			this, NAME_None, GetCurrentMontage(), FGameplayTagContainer());

		Task->OnCompleted.AddDynamic(
			this, &UToggleCombatModeAbility::HandleToggleCombatEnd);
		Task->OnCancelled.AddDynamic(
			this, &UToggleCombatModeAbility::HandleCancelAbilityTask);

		Task->ReadyForActivation();
	}
}

void UToggleCombatModeAbility::HandleUnEquip()
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
		UWeaponManager::UnEquipCharacterWeapon(
			Cast<ACharacter>(GetAvatarActorFromActorInfo())
			, CombatComponent->GetMainWeapon(), true);
		UWeaponManager::UnEquipCharacterWeapon(
			Cast<ACharacter>(GetAvatarActorFromActorInfo())
			, CombatComponent->GetSubWeapon(), false);
	}
}

void UToggleCombatModeAbility::HandleEquip()
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
		UWeaponManager::EquipCharacterWeapon(
			Cast<ACharacter>(GetAvatarActorFromActorInfo())
			, CombatComponent->GetMainWeapon(), true);
		UWeaponManager::EquipCharacterWeapon(
			Cast<ACharacter>(GetAvatarActorFromActorInfo())
			, CombatComponent->GetSubWeapon(), false);
	}
}

void UToggleCombatModeAbility::HandleToggleCombat()
{
	const bool IsCombat = UCombatManager::IsCharacterCombat(
		GetAbilitySystemComponentFromActorInfo());
	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, NlGameplayTags::State_Player_Idle
																	, IsCombat
																			? NlGameplayTags::State_Player_Equip
																			: NlGameplayTags::State_Player_UnEquip);
}

void UToggleCombatModeAbility::HandleToggleCombatEnd(
	FGameplayTag EventTag, FGameplayEventData EventData)
{
	const bool IsCombat = UCombatManager::IsCharacterCombat(
		GetAbilitySystemComponentFromActorInfo());

	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, IsCombat
																			? NlGameplayTags::State_Player_Equip
																			: NlGameplayTags::State_Player_UnEquip
																	, NlGameplayTags::State_Player_Idle);
	ClearDelegate();

	if (UCombatManager::IsCharacterCombat(
		GetAbilitySystemComponentFromActorInfo()))
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(
			NlGameplayTags::Status_Combat);
	}
	else
	{
		GetAbilitySystemComponentFromActorInfo()->AddLooseGameplayTag(
			NlGameplayTags::Status_Combat);
	}
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
}
