// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "NameLoser/Ability/DrawWeapon/AnimNotify/DrawAnimNotify.h"
#include "NameLoser/Ability/DrawWeapon/AnimNotify/DrawEndAnimNotify.h"
#include "NameLoser/Ability/SheathingWeapon//AnimNotify/SheathingEndAnimNotify.h"
#include "NameLoser/Characters/PlayerCharacter.h"
#include "NameLoser/SharedManager/AnimNotifyManager.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Bone"));
	WeaponSkeleton->SetupAttachment(RootComponent);

	WeaponCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Weapon Capsule"));
	WeaponCollisionComp->SetupAttachment(WeaponSkeleton);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponSkeleton;
}

void AWeaponBase::InitializeAnimation(APawn* OwnerPlayer)
{
	if (const TObjectPtr<UDrawAnimNotify> DrawNotify = UAnimNotifyManager::FindNotifyByClass<UDrawAnimNotify>(DrawAnimationMontage))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(OwnerPlayer))
		{
			Player->InitWeaponDrawRightBind(DrawNotify);
		}
	}
	
	if (const TObjectPtr<UDrawEndAnimNotify> DrawEndNotify = UAnimNotifyManager::FindNotifyByClass<UDrawEndAnimNotify>(DrawAnimationMontage))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(OwnerPlayer))
		{
			Player->InitWeaponDrawEndRightBind(DrawEndNotify);
		}
	}

	if (const TObjectPtr<UDrawEndAnimNotify> DrawEndNotify = UAnimNotifyManager::FindNotifyByClass<UDrawEndAnimNotify>(SheathingAnimationMontage))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(OwnerPlayer))
		{
			Player->InitWeaponDrawEndRightBind(DrawEndNotify);
		}
	}
	
	if (const TObjectPtr<USheathingEndAnimNotify> SheathingEndNotify = UAnimNotifyManager::FindNotifyByClass<USheathingEndAnimNotify>(SheathingAnimationMontage))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(OwnerPlayer))
		{
			Player->InitWeaponSheathingEndRightBind(SheathingEndNotify);
		}
	}
}


