// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Weapon/WeaponBase.h"
#include "ShieldBase.generated.h"

UCLASS()
class PROJECTNL_API AShieldBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShieldBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
