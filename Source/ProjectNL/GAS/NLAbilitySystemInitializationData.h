#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "NLAbilitySystemInitializationData.generated.h"

class UBaseInputTriggerAbility;
class UAttributeSet;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FNLAbilitySystemInitializationData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UAttributeSet>> AttributeSets;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FGameplayAttribute, float> AttributeBaseValues;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UBaseInputTriggerAbility>> GameplayAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UBaseInputTriggerAbility> FirstNameAbility;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UBaseInputTriggerAbility> SecondNameAbility;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UBaseInputTriggerAbility> ThirdNameAbility;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTagContainer GameplayTags;
};
