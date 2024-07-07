#include "WeaponBase.h"

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
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}


