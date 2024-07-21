#include "WeaponBase.h"

#include "ProjectNL/Character/Player/PlayerCharacter.h"
#include "ProjectNL/Component/CombatComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Bone"));
	WeaponSkeleton->SetupAttachment(RootComponent);

	WeaponCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Weapon Capsule"));
	WeaponCollisionComp->SetupAttachment(WeaponSkeleton);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner()))
	{
		Player->CombatComponent->OnNotifiedComboAttackStart.AddDynamic(this, &AWeaponBase::SetWeaponDamageable);
		Player->CombatComponent->OnNotifiedComboAttackEnd.AddDynamic(this, &AWeaponBase::UnsetWeaponDamageable);
	}
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::SetWeaponDamageable()
{
	WeaponCollisionComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
}

void AWeaponBase::UnsetWeaponDamageable()
{
	WeaponCollisionComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}


USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}


