// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Weapon/WeaponBase.h"
#include "OneHandDagger.generated.h"

UCLASS()
class PROJECTNL_API AOneHandDagger : public AWeaponBase
{
	GENERATED_BODY()

public:
	AOneHandDagger();

protected:
	virtual void BeginPlay() override;
};
