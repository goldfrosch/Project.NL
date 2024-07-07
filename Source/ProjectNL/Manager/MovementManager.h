// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MovementManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNL_API UMovementManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	static void Move(APawn* Entity, const FVector2D MoveTo);
};
