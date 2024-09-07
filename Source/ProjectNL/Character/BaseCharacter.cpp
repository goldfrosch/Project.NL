#include "BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Component/DamagedComponent.h"
#include "ProjectNL/Component/WidgetsComponent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"
#include "ProjectNL/Manager/WeaponManager.h"

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

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		UWeaponManager::EquipCharacterWeapon(Cast<ACharacter>(this)
																				, CombatComponent->GetMainWeapon()
																				, true);
		UWeaponManager::EquipCharacterWeapon(Cast<ACharacter>(this)
																				, CombatComponent->GetSubWeapon()
																				, false);
	}
	else
	{
		UWeaponManager::UnEquipCharacterWeapon(Cast<ACharacter>(this)
																					, CombatComponent->GetMainWeapon()
																					, true);
		UWeaponManager::UnEquipCharacterWeapon(Cast<ACharacter>(this)
																					, CombatComponent->GetSubWeapon()
																					, false);
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
