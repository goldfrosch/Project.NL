﻿#include "NLAbilitySystemComponent.h"

#include "NLAbilitySystemInitializationData.h"
#include "Ability/Utility/BaseInputTriggerAbility.h"


UNLAbilitySystemComponent::UNLAbilitySystemComponent()
{
	ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	SetIsReplicatedByDefault(true);
}

void UNLAbilitySystemComponent::InitializeAbilitySystem(
	const FNLAbilitySystemInitializationData& InitData)
{
	if (GetIsInitialized())
	{
		return;
	}

	if (GetOwnerRole() == ROLE_Authority)
	{
		if (!InitData.GameplayAbilities.IsEmpty())
		{
			for (TSubclassOf<UBaseInputTriggerAbility> Ability : InitData.
					GameplayAbilities)
			{
				UBaseInputTriggerAbility* InputAbility = Ability->GetDefaultObject<
					UBaseInputTriggerAbility>();

				GiveAbility(FGameplayAbilitySpec(
					Ability, InputAbility->GetAbilityLevel()
					, static_cast<uint32>(InputAbility->GetInputID()), this));
			}
		}
		if (!InitData.GameplayEffects.IsEmpty())
		{
			for (TSubclassOf<UGameplayEffect> Effect : InitData.GameplayEffects)
			{
				ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1
																	, MakeEffectContext());
			}
		}
	}

	if (!InitData.GameplayTags.IsEmpty())
	{
		AddLooseGameplayTags(InitData.GameplayTags);
	}


	SetIsInitialized(true);
}
