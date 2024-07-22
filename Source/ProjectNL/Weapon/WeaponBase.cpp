#include "WeaponBase.h"

#include "ProjectNL/Character/Player/PlayerCharacter.h"
#include "ProjectNL/Component/CombatComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Bone"));
	RootComponent = WeaponSkeleton;

	WeaponCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Weapon Capsule"));
	WeaponCollisionComp->SetupAttachment(WeaponSkeleton);
}	

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::InitEquipWeapon()
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetRootComponent()->GetAttachParent()->GetAttachmentRootActor()))
	{
		Player->CombatComponent->OnNotifiedComboAttackStart.AddDynamic(this, &AWeaponBase::SetWeaponDamageable);
		Player->CombatComponent->OnNotifiedComboAttackEnd.AddDynamic(this, &AWeaponBase::UnsetWeaponDamageable);

		WeaponCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::GiveDamage);
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

void AWeaponBase::GiveDamage(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Result: %s, %s"), *OverlappedComponent->GetName(), *OtherActor->GetName());
}


USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}


