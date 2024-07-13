// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "AbilitySystemComponent.h"
#include "ProjectNL/Attribute/BasicAttributeSet.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}

void ADefaultPlayerState::BeginPlay()
{
	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle =
			AbilitySystemComponent->
			GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute())
			.AddUObject(this, &ADefaultPlayerState::HealthChanged);
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

