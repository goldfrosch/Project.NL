#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Abilities/GameplayAbility.h"
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

	ETriggerEvent InputPressedTriggerType = ETriggerEvent::Started;

	ETriggerEvent InputReleasedTriggerType = ETriggerEvent::Completed;

	FEnhancedInputActionValueBinding* InputValue;

protected:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo
													, const FGameplayAbilitySpec& Spec) override;

	void SetupEnhancedInputBindings(const FGameplayAbilityActorInfo* ActorInfo
																	, const FGameplayAbilitySpec& Spec);

	void HandleInputPressedEvent(const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilitySpecHandle SpecHandle);

	void HandleInputReleasedEvent(const FGameplayAbilityActorInfo* ActorInfo
																, const FGameplayAbilitySpecHandle SpecHandle);

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilitySpec& Spec) override;
};
