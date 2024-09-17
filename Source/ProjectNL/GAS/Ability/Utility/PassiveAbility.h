#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PassiveAbility.generated.h"

UCLASS()
class PROJECTNL_API UPassiveAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPassiveAbility();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle
															, const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilityActivationInfo
															ActivationInfo
															, const FGameplayEventData*
															TriggerEventData) override;

	virtual void OnActivateAbility();

	// repeat time이 만약 -1이면 한번 실행하고 그 이후 사용하지 않음
	UPROPERTY(EditAnywhere, Category = "Input")
	float RepeatTime = -1;

private:
	FTimerHandle PassiveTimerHandle;
};
