#include "Sprint.h"

#include "AbilitySystemComponent.h"

USprint::USprint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool USprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle
																, const FGameplayAbilityActorInfo* ActorInfo
																, const FGameplayTagContainer* SourceTags
																, const FGameplayTagContainer* TargetTags
																, FGameplayTagContainer* OptionalRelevantTags)
const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags
																, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void USprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle
															, const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilityActivationInfo
															ActivationInfo
															, const FGameplayEventData* TriggerEventData)
{
	if (BuffEffect)
	{
		EffectContext = GetAbilitySystemComponentFromActorInfo()->
			MakeEffectContext();
		EffectContext.AddSourceObject(GetAvatarActorFromActorInfo());

		SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			BuffEffect, 1.0f, EffectContext);
		if (SpecHandle.IsValid())
		{
			GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(
				*SpecHandle.Data.Get());
		}
	}
}

void USprint::CancelAbility(const FGameplayAbilitySpecHandle Handle
														, const FGameplayAbilityActorInfo* ActorInfo
														, const FGameplayAbilityActivationInfo
														ActivationInfo, bool bReplicateCancelAbility)
{
	GetAbilitySystemComponentFromActorInfo()->
		RemoveActiveGameplayEffectBySourceEffect(BuffEffect
																						, GetAbilitySystemComponentFromActorInfo());
	EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility, false);
}
