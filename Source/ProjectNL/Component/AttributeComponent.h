// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS()
class PROJECTNL_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();
	void InitAttributeChanged();

private:
	FOnGameplayAttributeValueChange MovementSpeedDelegateChanged;
	void MovementSpeedChanged(const FOnAttributeChangeData& Data) const;
};
