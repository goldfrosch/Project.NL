// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Weapon/WeaponBase.h"
#include "OneHandSword.generated.h"

UCLASS()
class PROJECTNL_API AOneHandSword : public AWeaponBase
{
	GENERATED_BODY()

public:
	AOneHandSword();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
