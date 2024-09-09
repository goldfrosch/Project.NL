// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ProjectNL/Helper/UtilHelper.h"
#include "NLAbilitySystemComponent.generated.h"


struct FNLAbilitySystemInitializationData;
struct FInitGameplayAbilitySystem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTNL_API UNLAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UNLAbilitySystemComponent();

	void InitializeAbilitySystem(
		const FNLAbilitySystemInitializationData& InitData, AActor* InOwningActor
		, AActor* InAvatarActor);

	UPROPERTY()
	const UAttributeSet* AttributeSet;

private:
	bool bAbilitySystemInitialized = false;
	GETTER_SETTER(bool, bAbilitySystemInitialized)
};
