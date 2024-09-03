#include "WeaponBase.h"

#include "Kismet/GameplayStatics.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));

	WeaponSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(
		TEXT("Weapon Bone"));
	WeaponSkeleton->SetupAttachment(RootComponent);

	WeaponCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(
		TEXT("Weapon Capsule"));
	WeaponCollisionComp->SetupAttachment(WeaponSkeleton);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	WeaponCollisionComp->OnComponentBeginOverlap.AddDynamic(
		this, &ThisClass::OnBeginOverlap);
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
	WeaponCollisionComp->SetCollisionEnabled(
		ECollisionEnabled::Type::NoCollision);
}

void AWeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent
																, AActor* OtherActor
																, UPrimitiveComponent* OtherComp
																, int32 OtherBodyIndex, bool bFromSweep
																, const FHitResult& SweepResult)
{
	if (GetAttachParentActor())
	{
		if (GetAttachParentActor() != OtherActor)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 20
																		, GetAttachParentActor()->
																		GetInstigatorController(), this
																		, UDamageType::StaticClass());
		}
	}
}


USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}
