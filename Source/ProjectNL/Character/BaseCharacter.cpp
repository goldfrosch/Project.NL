#include "BaseCharacter.h"
#include "ProjectNL/GAS/Attribute/BasicAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(
		TEXT("AbilitySystemComponent"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(
		TEXT("Combat Component"));
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

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	SetOwner(NewController);
}

void ABaseCharacter::Jump()
{
	Super::Jump();
	AbilitySystemComponent->AddLooseGameplayTag(
		NlGameplayTags::State_Player_Jump);
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
	Super::StopJumping();
	AbilitySystemComponent->RemoveLooseGameplayTag(
		NlGameplayTags::State_Player_Jump);
	AbilitySystemComponent->RemoveLooseGameplayTag(
		NlGameplayTags::State_Player_DoubleJump);
}
