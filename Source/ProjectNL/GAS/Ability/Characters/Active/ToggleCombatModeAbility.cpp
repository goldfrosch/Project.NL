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
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}


void UToggleCombatModeAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo
	, const FGameplayEventData* TriggerEventData)
{
	if (!FStateHelper::IsPlayerIdle(GetAbilitySystemComponentFromActorInfo()))
	{
		return;
	}

	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		ActorInfo->AvatarActor.Get()))
	{
		const AWeaponBase* MainWeapon = OwnerCharacter->CombatComponent->
																										GetMainWeapon();
		const AWeaponBase* SubWeapon = OwnerCharacter->CombatComponent->
																									GetSubWeapon();

		HandleToggleCombat();

		if (FStateHelper::IsCharacterCombat(
			GetAbilitySystemComponentFromActorInfo()))
		{
			SetCurrentMontage(UCombatManager::GetEquipAnimation(
				CombatAnimData
				, OwnerCharacter->CombatComponent->GetPlayerCombatWeaponState()));
			// 애니메이션 Notify 추가
			if (const TObjectPtr<UPutWeaponNotify> PutWeaponNotify =
				UAnimNotifyManager::FindNotifyByClass<UPutWeaponNotify>(
					GetCurrentMontage()))
			{
				// TODO: 추후 별도의 Anim과 Notify 정보를 저장하는 Ability를 생성 후 이전
				// 현재는 여러번 Notify가 걸리는 이슈가 존재함.
				PutWeaponNotify->OnNotified.AddDynamic(
					this, &UToggleCombatModeAbility::HandleEquip);
			}
		}
		else
		{
			SetCurrentMontage(UCombatManager::GetUnEquipAnimation(
				CombatAnimData
				, OwnerCharacter->CombatComponent->GetPlayerCombatWeaponState()));
			// 애니메이션 Notify 추가
			if (const TObjectPtr<UGrabWeaponNotify> GrabWeaponNotify =
				UAnimNotifyManager::FindNotifyByClass<UGrabWeaponNotify>(
					GetCurrentMontage()))
			{
				GrabWeaponNotify->OnNotified.AddDynamic(
					this, &UToggleCombatModeAbility::HandleUnEquip);
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
		const UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
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
		const UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
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
	const bool IsCombat = FStateHelper::IsCharacterCombat(
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
	const bool IsCombat = FStateHelper::IsCharacterCombat(
		GetAbilitySystemComponentFromActorInfo());

	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, IsCombat
																			? NlGameplayTags::State_Player_Equip
																			: NlGameplayTags::State_Player_UnEquip
																	, NlGameplayTags::State_Player_Idle);
	if (FStateHelper::IsCharacterCombat(GetAbilitySystemComponentFromActorInfo()))
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
	const bool IsCombat = FStateHelper::IsCharacterCombat(
		GetAbilitySystemComponentFromActorInfo());

	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, IsCombat
																			? NlGameplayTags::State_Player_Equip
																			: NlGameplayTags::State_Player_UnEquip
																	, NlGameplayTags::State_Player_Idle);
}
