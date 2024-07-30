#include "ComboAttack.h"

#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"

UComboAttack::UComboAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag AbilityTag = NlGameplayTags::Ability_Combat_Attack;
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);
	ActivationBlockedTags.AddTag(NlGameplayTags::Ability_Combat);
}

void UComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle
																	, const FGameplayAbilityActorInfo* ActorInfo
																	, const FGameplayAbilityActivationInfo
																	ActivationInfo
																	, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
							, true);
	}

	if (ABaseCharacter* CurrentCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		return;
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
						, true);
}

void UComboAttack::OnCompleted(FGameplayTag EventTag
															, FGameplayEventData EventData)
{
}
