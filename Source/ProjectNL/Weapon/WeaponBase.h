// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"

#include "WeaponType.h"

#include "WeaponBase.generated.h"

UCLASS()
class PROJECTNL_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;
	
	USkeletalMeshComponent* GetWeaponMesh() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	EUEquippedHandType EquippedHandType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	EUWeaponType WeaponType;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponSkeleton;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* WeaponCollisionComp;
};
