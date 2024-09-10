// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Weapon/WeaponBase.h"
#include "GreatSword.generated.h"

UCLASS()
class PROJECTNL_API AGreatSword : public AWeaponBase
{
	GENERATED_BODY()

public:
	AGreatSword();

protected:
	virtual void BeginPlay() override;
};
