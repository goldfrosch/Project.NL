#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ComboAttack.generated.h"

UCLASS()
class PROJECTNL_API UComboAttack : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UComboAttack();
	
	uint8 GetComboIndex() const { return ComboIndex; }
	uint8 GetMaxCombo() const { return MaxCombo; }

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
private:
	bool IsNextCombo = false;
	uint8 ComboIndex = 0;
	uint8 MaxCombo = 0;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> GEDamage;
	
	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);
};
