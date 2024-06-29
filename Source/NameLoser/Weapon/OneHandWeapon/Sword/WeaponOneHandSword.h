// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NameLoser/Weapon/WeaponBase.h"
#include "WeaponOneHandSword.generated.h"

UCLASS()
class NAMELOSER_API AWeaponOneHandSword : public AWeaponBase
{
	GENERATED_BODY()

public:
	AWeaponOneHandSword();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
