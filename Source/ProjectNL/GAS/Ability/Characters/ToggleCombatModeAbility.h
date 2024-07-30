// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/GAS/Ability/Utility/BaseInputTriggerAbility.h"
#include "ToggleCombatModeAbility.generated.h"

UCLASS()
class PROJECTNL_API UToggleCombatModeAbility : public UBaseInputTriggerAbility
{
	GENERATED_BODY()

public:
	UToggleCombatModeAbility(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle
															, const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilityActivationInfo
															ActivationInfo
															, const FGameplayEventData*
															TriggerEventData) override;

	virtual void FinishDestroy() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat|Anim"
		, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle CombatAnimData;

	UFUNCTION()
	void Sheath();

	UFUNCTION()
	void UnSheath();
};
