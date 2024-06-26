// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.h"
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
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponSkeleton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets, meta = (AllowPrivateAccess = "true"))
	EUWeaponType WeaponType;
};