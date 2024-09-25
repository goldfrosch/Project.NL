#include "BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Component/DamagedComponent.h"
#include "ProjectNL/Component/WidgetsComponent.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"
#include "ProjectNL/Weapon/WeaponBase.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
{
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(
		TEXT("Combat Component"));
	WidgetsComponent = CreateDefaultSubobject<UWidgetsComponent>(
		TEXT("Widgets Component"));
	DamagedComponent = CreateDefaultSubobject<UDamagedComponent>(
		TEXT("Damaged Component"));

	WidgetsComponent->FixedViewWidget->SetupAttachment(GetCapsuleComponent());
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitCharacterWeapon();
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

void ABaseCharacter::InitCharacterWeapon()
{
	CombatComponent->SetMainWeapon(this->GetWorld()->SpawnActor<AWeaponBase>(
		CombatComponent->GetMainWeaponTemplate()));
	CombatComponent->SetSubWeapon(this->GetWorld()->SpawnActor<AWeaponBase>(
		CombatComponent->GetSubWeaponTemplate()));

	if (GetIsFirstEquip())
	{
		if (IsValid(CombatComponent->GetMainWeapon()))
		{
			CombatComponent->GetMainWeapon()->EquipCharacterWeapon(this, true);
		}
		if (IsValid(CombatComponent->GetSubWeapon()))
		{
			CombatComponent->GetSubWeapon()->EquipCharacterWeapon(this, false);
		}
	}
	else
	{
		if (IsValid(CombatComponent->GetMainWeapon()))
		{
			CombatComponent->GetMainWeapon()->UnEquipCharacterWeapon(this, true);
		}
		if (IsValid(CombatComponent->GetSubWeapon()))
		{
			CombatComponent->GetSubWeapon()->UnEquipCharacterWeapon(this, false);
		}
	}
}

float ABaseCharacter::TakeDamage(float DamageAmount
																, const FDamageEvent& DamageEvent
																, AController* EventInstigator
																, AActor* DamageCauser)
{
	DamagedComponent->HandleDamaged(DamageCauser);

	return DamageAmount;
}

void ABaseCharacter::Server_ApplyGameplayEffectToSelf_Implementation(
	TSubclassOf<UGameplayEffect> Effect, const uint32 Level)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		Server_ApplyGameplayEffectToSelf(Effect);
		return;
	}

	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		Effect.GetDefaultObject(), Level
		, AbilitySystemComponent->MakeEffectContext());
}

void
ABaseCharacter::Server_RemoveActiveGameplayEffectBySourceEffect_Implementation(
	TSubclassOf<UGameplayEffect> Effect)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		Server_ApplyGameplayEffectToSelf(Effect);
		return;
	}

	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(
		Effect, AbilitySystemComponent);
}
