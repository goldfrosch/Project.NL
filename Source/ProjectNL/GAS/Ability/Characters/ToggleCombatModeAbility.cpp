#include "ToggleCombatModeAbility.h"

#include "AbilitySystemComponent.h"
#include "ProjectNL/Animation/Characters/Sheathing/GrabWeaponNotify.h"
#include "ProjectNL/Animation/Characters/Sheathing/PutWeaponNotify.h"
#include "ProjectNL/Animation/Characters/Sheathing/UnSheathingEndNotify.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Manager/CombatManager.h"
#include "ProjectNL/Manager/WeaponManager.h"

UToggleCombatModeAbility::UToggleCombatModeAbility(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
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
		const AWeaponBase* MainWeapon = OwnerCharacter->CombatComponent->
																										GetMainWeapon();
		const AWeaponBase* SubWeapon = OwnerCharacter->CombatComponent->
																									GetSubWeapon();


		UAnimMontage* SheathingAnimMontage;
		if (OwnerCharacter->AbilitySystemComponent->HasMatchingGameplayTag(
			FGameplayTag::RequestGameplayTag(
				NlGameplayTags::Status_Combat.GetModuleName())))
		{
			SheathingAnimMontage = UCombatManager::GetSheathingAnimation(
				CombatAnimData, MainWeapon, SubWeapon);
			// 애니메이션 Notify 추가
			if (const TObjectPtr<UPutWeaponNotify> PutWeaponNotify =
				UAnimNotifyManager::FindNotifyByClass<UPutWeaponNotify>(
					SheathingAnimMontage))
			{
				PutWeaponNotify->OnNotified.Clear();
				PutWeaponNotify->OnNotified.AddDynamic(
					this, &UToggleCombatModeAbility::Sheath);
			}
		}
		else
		{
			SheathingAnimMontage = UCombatManager::GetUnSheathingAnimation(
				CombatAnimData, MainWeapon, SubWeapon);
			// 애니메이션 Notify 추가
			if (const TObjectPtr<UGrabWeaponNotify> GrabWeaponNotify =
				UAnimNotifyManager::FindNotifyByClass<UGrabWeaponNotify>(
					SheathingAnimMontage))
			{
				GrabWeaponNotify->OnNotified.Clear();
				GrabWeaponNotify->OnNotified.AddDynamic(
					this, &UToggleCombatModeAbility::UnSheath);
			}
		}
	}
}

void UToggleCombatModeAbility::UnSheath()
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		const UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
		UWeaponManager::UnSheathCharacterWeapon(
			Cast<ACharacter>(GetAvatarActorFromActorInfo())
			, CombatComponent->GetMainWeapon(), true);
		UWeaponManager::UnSheathCharacterWeapon(
			Cast<ACharacter>(GetAvatarActorFromActorInfo())
			, CombatComponent->GetSubWeapon(), false);
	}
}

void UToggleCombatModeAbility::Sheath()
{
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		const UCombatComponent* CombatComponent = OwnerCharacter->CombatComponent;
		UWeaponManager::SheathCharacterWeapon(Cast<ACharacter>(this)
																					, CombatComponent->GetMainWeapon()
																					, true);
		UWeaponManager::SheathCharacterWeapon(Cast<ACharacter>(this)
																					, CombatComponent->GetSubWeapon()
																					, false);
	}
}

void UToggleCombatModeAbility::FinishDestroy()
{
	if (GetAbilitySystemComponentFromActorInfo())
	{
		const bool IsCombat = GetAbilitySystemComponentFromActorInfo()->
			HasMatchingGameplayTag(
				FGameplayTag::RequestGameplayTag(
					NlGameplayTags::Status_Combat.GetModuleName()));
		ActivationOwnedTags.AddTag(IsCombat
																? NlGameplayTags::Ability_Combat_Sheathing
																: NlGameplayTags::Ability_Combat_UnSheathing);
	}
}
