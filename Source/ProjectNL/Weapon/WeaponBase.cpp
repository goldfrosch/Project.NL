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

	WeaponCollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// TODO: ECC_Pawn -> Custom ECC로 전환
	WeaponCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}	

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	WeaponCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::GiveDamage);
}

void AWeaponBase::InitEquipWeapon()
{
	if (USceneComponent* Parent = GetRootComponent()->GetAttachParent())
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(Parent->GetAttachmentRootActor()))
		{
			Player->CombatComponent->OnNotifiedComboAttackStart.AddDynamic(this, &AWeaponBase::SetWeaponDamageable);
			Player->CombatComponent->OnNotifiedComboAttackEnd.AddDynamic(this, &AWeaponBase::UnsetWeaponDamageable);
		}
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
	if (const USceneComponent* Parent = GetRootComponent()->GetAttachParent())
	{
		// 나랑 동일한 캐릭터 or Pawn인지 확인 한 후 동일하면 진행하지 않음
		if (const APawn* Owner = Cast<APawn>(Parent->GetAttachmentRootActor()))
		{
			if (OtherActor == Owner) return;
		}
	}
	
	UE_LOG(LogTemp, Display, TEXT("Result: %s, %s"), *OverlappedComponent->GetName(), *OtherActor->GetName());
}


USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}


