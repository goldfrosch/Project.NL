// Fill out your copyright notice in the Description page of Project Settings.


#include "NLAbilitySystemComponent.h"

#include "Ability/Utility/AbilityBindingInterface.h"

UNLAbilitySystemComponent::UNLAbilitySystemComponent()
{
}

void UNLAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	if (const IAbilityBindingInterface* ABI = Cast<IAbilityBindingInterface>(
		GetAvatarActor_Direct()))
	{
		ABI->BindAbility(AbilitySpec);
	}

	Super::OnGiveAbility(AbilitySpec);
}
