#include "BaseCharacter.h"
#include "ProjectNL/Attribute/BasicAttributeSet.h"
#include "AbilitySystemComponent.h"

ABaseCharacter::ABaseCharacter(const class FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(AbilitySystemComponent))
	{
		AttributeSet = AbilitySystemComponent->GetSet<UBasicAttributeSet>();
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
