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
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetRootComponent()->GetAttachParent()->GetAttachmentRootActor()))
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

void AWeaponBase::GiveDamage(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: 내 자신도 Overlap 되는 이슈 확인 후 수정
	UE_LOG(LogTemp, Display, TEXT("Result: %s, %s"), *OverlappedComponent->GetName(), *SweepResult.GetActor()->GetName());
}


USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}


