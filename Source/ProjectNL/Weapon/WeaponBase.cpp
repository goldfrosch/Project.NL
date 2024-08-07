﻿#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(
		TEXT("Weapon Bone"));
	RootComponent = WeaponSkeleton;

	WeaponCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(
		TEXT("Weapon Capsule"));

	WeaponCollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// TODO: ECC_Pawn -> Custom ECC로 전환
	WeaponCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	WeaponCollisionComp->OnComponentBeginOverlap.AddDynamic(
		this, &AWeaponBase::GiveDamage);
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::SetWeaponDamageable() const
{
	WeaponCollisionComp->SetCollisionEnabled(
		ECollisionEnabled::Type::QueryAndPhysics);
}

void AWeaponBase::UnsetWeaponDamageable() const
{
	WeaponCollisionComp->
		SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AWeaponBase::GiveDamage(UPrimitiveComponent* OverlappedComponent
														, AActor* OtherActor, UPrimitiveComponent* OtherComp
														, int32 OtherBodyIndex, bool bFromSweep
														, const FHitResult& SweepResult)
{
	if (const USceneComponent* Parent = GetRootComponent()->GetAttachParent())
	{
		// 나랑 동일한 캐릭터 or Pawn인지 확인 한 후 동일하면 진행하지 않음
		if (const APawn* PawnOwner = Cast<APawn>(Parent->GetAttachmentRootActor()))
		{
			if (OtherActor == PawnOwner)
			{
				return;
			}
		}
	}

	OnNotifiedAttack.Broadcast(OverlappedComponent, OtherActor, OtherComp
														, OtherBodyIndex, bFromSweep, SweepResult);
}


USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}
