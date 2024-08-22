#include "PlayerStateBase.h"

#include "ProjectNL/GAS/NLAbilitySystemComponent.h"

APlayerStateBase::APlayerStateBase()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UNLAbilitySystemComponent>(
		"Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(
		EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
