#include "NLAbilitySystemComponent.h"

#include "NLAbilitySystemInitializationData.h"


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
			for (const TSubclassOf<UGameplayAbility> Ability : InitData.
					GameplayAbilities)
			{
				GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
			}
		}
		if (!InitData.GameplayTags.IsEmpty())
		{
			AddLooseGameplayTags(InitData.GameplayTags);
		}
	}
}
