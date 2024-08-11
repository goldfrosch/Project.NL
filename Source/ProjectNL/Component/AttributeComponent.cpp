#include "AttributeComponent.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/GAS/Attribute/BasicAttributeSet.h"

UAttributeComponent::UAttributeComponent()
{
}

void UAttributeComponent::InitAttributeChanged()
{
	if (const ABaseCharacter* OwnerActor = Cast<ABaseCharacter>(GetOwner()))
	{
		MovementSpeedDelegateChanged = OwnerActor->AbilitySystemComponent->
																							GetGameplayAttributeValueChangeDelegate(
																								OwnerActor->AttributeSet->
																								GetMovementSpeedAttribute());
		MovementSpeedDelegateChanged.AddUObject(
			this, &UAttributeComponent::MovementSpeedChanged);
	}
}

void UAttributeComponent::MovementSpeedChanged(
	const FOnAttributeChangeData& Data) const
{
	if (const ABaseCharacter* OwnerActor = Cast<ABaseCharacter>(GetOwner()))
	{
		OwnerActor->GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
	}
}
