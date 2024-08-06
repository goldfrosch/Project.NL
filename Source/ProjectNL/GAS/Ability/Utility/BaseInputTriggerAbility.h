// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseInputTriggerAbility.generated.h"

struct FInputActionValue;

UCLASS()
class PROJECTNL_API UBaseInputTriggerAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseInputTriggerAbility(const FObjectInitializer& ObjectInitializer);
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle
														, const FGameplayAbilityActorInfo* ActorInfo
														, const FGameplayAbilityActivationInfo
														ActivationInfo) override;

	FORCEINLINE void SetCancelAbilityOnInputReleased(const bool IsReleased)
	{
		bCancelAbilityOnInputReleased = IsReleased;
	}

protected:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

	TArray<uint32> TriggeredEventHandles;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle
															, const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilityActivationInfo
															ActivationInfo
															, const FGameplayEventData*
															TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle
													, const FGameplayAbilityActorInfo* ActorInfo
													, const FGameplayAbilityActivationInfo ActivationInfo
													, bool bReplicateEndAbility
													, bool bWasCancelled) override;
	virtual void OnTriggeredInputAction(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability"
		, meta = (AllowPrivateAccess = true))
	bool bCancelAbilityOnInputReleased;
};
