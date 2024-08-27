﻿#include "NLAbilitySystemComponent.h"

#include "NLAbilitySystemInitializationData.h"
#include "Ability/Utility/BaseInputTriggerAbility.h"


UNLAbilitySystemComponent::UNLAbilitySystemComponent()
{
	ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	SetIsReplicatedByDefault(true);
}

void UNLAbilitySystemComponent::InitializeAbilitySystem(
	const FNLAbilitySystemInitializationData& InitData, AActor* InOwningActor
	, AActor* InAvatarActor)
{
	if (GetbAbilitySystemInitialized())
	{
		return;
	}

	SetbAbilitySystemInitialized(true);

	InitAbilityActorInfo(InOwningActor, InAvatarActor);

	if (GetOwnerActor()->HasAuthority())
	{
		if (!InitData.AttributeSets.IsEmpty())
		{
			for (const TSubclassOf<UAttributeSet> AttributeSetClass : InitData.
					AttributeSets)
			{
				GetOrCreateAttributeSubobject(AttributeSetClass);
			}
		}

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
	}
	if (!InitData.GameplayTags.IsEmpty())
	{
		AddLooseGameplayTags(InitData.GameplayTags);
	}
}