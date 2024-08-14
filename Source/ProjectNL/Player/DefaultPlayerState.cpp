#include "DefaultPlayerState.h"
#include "AbilitySystemComponent.h"
#include "ProjectNL/GAS/Attribute/PlayerAttributeSet.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(
		TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(
		EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(
		TEXT("Attributeset"));

	NetUpdateFrequency = 100.0f;
}

void ADefaultPlayerState::BeginPlay()
{
	if (AbilitySystemComponent)
	{
		if (AttributeSet)
		{
			AttributeSet->InitBaseAttribute();
		}
		AbilitySystemComponent->
			GetGameplayAttributeValueChangeDelegate(
				AttributeSet->GetHealthAttribute()).AddUObject(
				this, &ADefaultPlayerState::HealthChanged);
	}
}

void ADefaultPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Display, TEXT("%f"), Data.NewValue);
}

void ADefaultPlayerState::Tick(float DeltaSeconds)
{
	// TODO: GameplayEffect로 체력 깎아보기 테스트 진행
}
