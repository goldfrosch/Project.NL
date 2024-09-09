﻿#include "Sprint.h"

#include "AbilitySystemComponent.h"

USprint::USprint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bActivateAbilityInputTrigger = true;
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

// TODO: Release될때만 실행되는 이슈 수정
void USprint::OnTriggeredInputAction(const FInputActionValue& Value)
{
	Super::OnTriggeredInputAction(Value);

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
