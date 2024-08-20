// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/GAS/Ability/Utility/BaseInputTriggerAbility.h"
#include "Look.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNL_API ULook : public UBaseInputTriggerAbility
{
	GENERATED_BODY()

public:
	ULook(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnTriggeredInputAction(const FInputActionValue& Value);
};
