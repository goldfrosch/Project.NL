﻿#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/GAS/Ability/Utility/BaseInputTriggerAbility.h"
#include "DoubleJump.generated.h"

UCLASS()
class PROJECTNL_API UDoubleJump : public UBaseInputTriggerAbility
{
	GENERATED_BODY()

public:
	UDoubleJump(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle
															, const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilityActivationInfo
															ActivationInfo
															, const FGameplayEventData*
															TriggerEventData) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle
																	, const FGameplayAbilityActorInfo* ActorInfo
																	, const FGameplayTagContainer* SourceTags
																	, const FGameplayTagContainer* TargetTags
																	, FGameplayTagContainer* OptionalRelevantTags)
	const override;
};
