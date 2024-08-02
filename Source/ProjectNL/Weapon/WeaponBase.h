// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "GameFramework/Actor.h"
#include "ProjectNL/Helper/UtilHelper.h"

#include "WeaponBase.generated.h"

UCLASS()
class PROJECTNL_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetWeaponMesh() const;


	void InitEquipWeapon();

	UFUNCTION()
	void SetWeaponDamageable();

	UFUNCTION()
	void UnsetWeaponDamageable();

	UFUNCTION()
	void GiveDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
									, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
									, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponSkeleton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* WeaponCollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	EUEquippedHandType EquippedHandType;
	GETTER(EUEquippedHandType, EquippedHandType)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	EUWeaponType WeaponType;
	GETTER(EUWeaponType, WeaponType)
};
