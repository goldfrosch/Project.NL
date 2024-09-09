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
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(
		EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		if (const UPlayerAttributeSet* PlayerAttributeSet = Cast<
			UPlayerAttributeSet>(AbilitySystemComponent->AttributeSet))
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				PlayerAttributeSet->GetMovementSpeedAttribute()).AddUObject(
				this, &ThisClass::MovementSpeedChanged);
		}
	}
}

void APlayerStateBase::MovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	const float MovementSpeed = Data.NewValue;

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetPawn()))
	{
		UE_LOG(LogTemp, Display, TEXT("테스트 Value: %f"), MovementSpeed);
		Player->GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	}
}
