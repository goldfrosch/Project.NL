#include "WeaponBase.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectNL/Character/BaseCharacter.h"

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


	WeaponCollisionComp->SetCollisionEnabled(
		ECollisionEnabled::Type::NoCollision);

	WeaponCollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponCollisionComp->SetGenerateOverlapEvents(true);

	WeaponCollisionComp->
		SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	WeaponCollisionComp->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	WeaponCollisionComp->SetCollisionResponseToChannel(
		ECC_WorldStatic, ECR_Overlap);
	WeaponCollisionComp->SetCollisionResponseToChannel(
		ECC_WorldDynamic, ECR_Overlap);
	WeaponCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	WeaponCollisionComp->SetCollisionResponseToChannel(
		ECC_PhysicsBody, ECR_Overlap);
	WeaponCollisionComp->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	WeaponCollisionComp->SetCollisionResponseToChannel(
		ECC_Destructible, ECR_Overlap);
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

void AWeaponBase::EquipCharacterWeapon(ACharacter* Character, const bool IsMain)
{
	const FString AttachSocket = "weapon";
	const FString Position = IsMain ? "_r" : "_l";

	AttachToComponent(Character->GetMesh()
										, FAttachmentTransformRules::SnapToTargetIncludingScale
										, *(AttachSocket + Position));
}

void AWeaponBase::UnEquipCharacterWeapon(const bool IsMain)
{
	if (const ACharacter* Character = Cast<ACharacter>(GetAttachParentActor()))
	{
		const FString Position = IsMain ? "_r" : "_l";
		const FString AttachSocket = "weapon_" +
			FEnumHelper::GetClassEnumKeyAsString(GetAttachPosition()).ToLower();

		AttachToComponent(Character->GetMesh()
											, FAttachmentTransformRules::SnapToTargetIncludingScale
											, *(AttachSocket + Position));
	}
}

void AWeaponBase::SwapTwoHandWeapon()
{
	if (GetEquippedHandType() != EUEquippedHandType::TwoHand)
	{
		return;
	}
	if (const ACharacter* Character = Cast<ACharacter>(GetAttachParentActor()))
	{
		AttachToComponent(Character->GetMesh()
											, FAttachmentTransformRules::SnapToTargetIncludingScale
											, "weapon_twoHand");
	}
}


void AWeaponBase::UnEquipCharacterWeapon(ACharacter* Character
																				, const bool IsMain)
{
	const FString Position = IsMain ? "_r" : "_l";
	const FString AttachSocket = "weapon_" + FEnumHelper::GetClassEnumKeyAsString(
		GetAttachPosition()).ToLower();

	AttachToComponent(Character->GetMesh()
										, FAttachmentTransformRules::SnapToTargetIncludingScale
										, *(AttachSocket + Position));
}
