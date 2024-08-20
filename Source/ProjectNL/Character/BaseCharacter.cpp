#include "BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Component/WidgetsComponent.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"
#include "ProjectNL/Manager/WeaponManager.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UNLAbilitySystemComponent>(
		TEXT("AbilitySystemComponent"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(
		TEXT("Combat Component"));
	WidgetsComponent = CreateDefaultSubobject<UWidgetsComponent>(
		TEXT("Widgets Component"));

	WidgetsComponent->FixedViewWidget->SetupAttachment(GetCapsuleComponent());
}

void ABaseCharacter::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CombatComponent);
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
