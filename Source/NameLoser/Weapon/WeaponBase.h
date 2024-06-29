// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


UCLASS()
class NAMELOSER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;
	
	USkeletalMeshComponent* GetWeaponMesh() const;

	UFUNCTION()
	void InitializeAnimation(APawn* OwnerPlayer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	UAnimMontage* DrawAnimationMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	UAnimMontage* SheathingAnimationMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TArray<UAnimMontage*> LightAttackMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TArray<UAnimMontage*> AttackComboMontage;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponSkeleton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	EUWeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* WeaponCollisionComp;

};