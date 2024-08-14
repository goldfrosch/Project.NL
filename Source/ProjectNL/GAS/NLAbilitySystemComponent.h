// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NLAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTNL_API UNLAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UNLAbilitySystemComponent();

protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
};
