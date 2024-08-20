#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "NLAbilitySystemInitializationData.generated.h"

class UAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FNLAbilitySystemInitializationData
{
	GENERATED_BODY()

	// An array of Attribute Sets to create.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UAttributeSet>> AttributeSets;

	// A map of Attributes / float used to set base values.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FGameplayAttribute, float> AttributeBaseValues;

	// An Array of Gameplay Abilities to give.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;

	// An array of Gameplay Effects to apply.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	// A container of GameplayTags to apply.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTagContainer GameplayTags;
};
