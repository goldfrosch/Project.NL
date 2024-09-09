﻿#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Abilities/GameplayAbility.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "BaseInputTriggerAbility.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS()
class PROJECTNL_API UBaseInputTriggerAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseInputTriggerAbility(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere
		, Category = "Custom Gameplay Ability")
	bool ActivateAbilityOnGranted = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* ActivationInputAction = nullptr;

	GETTER(EInputIDType, InputID)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActivateAbilityInputTrigger;

protected:
	uint32 TriggeredEventHandle = -1;

	void SetupEnhancedInputBindings(const FGameplayAbilityActorInfo* ActorInfo
																	, const FGameplayAbilitySpec& Spec);

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo
													, const FGameplayAbilitySpec& Spec) override;

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilitySpec& Spec) override;

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

private:
	// InputID가 -1인 경우 InputID를 할당받지 않은 상태라고 인지함
	UPROPERTY(EditAnywhere, Category = "Input", meta=(AllowPrivateAccess="true"))
	EInputIDType InputID = EInputIDType::None;

	void OnAbilityInputPressed(const FGameplayAbilityActorInfo* ActorInfo);

	void OnAbilityInputReleased(const FGameplayAbilityActorInfo* ActorInfo);

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle
														, const FGameplayAbilityActorInfo* ActorInfo
														, const FGameplayAbilityActivationInfo
														ActivationInfo) override;
};
