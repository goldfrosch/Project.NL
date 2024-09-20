#include "PlayerStateBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectNL/Character/Player/PlayerCharacter.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"
#include "ProjectNL/GAS/Attribute/PlayerAttributeSet.h"

APlayerStateBase::APlayerStateBase()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UNLAbilitySystemComponent>(
		"Ability System Component");
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(
		"Player Attribute Set");
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerStateBase::BeginPlay()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetMovementSpeedAttribute()).AddUObject(
			this, &ThisClass::MovementSpeedChanged);
	}
}

void APlayerStateBase::MovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	const float MovementSpeed = Data.NewValue;

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetPawn()))
	{
		Player->GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	}
}
