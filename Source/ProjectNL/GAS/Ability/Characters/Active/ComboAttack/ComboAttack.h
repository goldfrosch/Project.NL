#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ProjectNL/GAS/Ability/Utility/BaseInputTriggerAbility.h"
#include "ComboAttack.generated.h"

enum class EHandEquipStatus : uint8;
class UComboAttackNotifyState;
class UPlayMontageWithEvent;

UCLASS()
class PROJECTNL_API UComboAttack : public UBaseInputTriggerAbility
{
	GENERATED_BODY()

public:
	UComboAttack(const FObjectInitializer& ObjectInitializer);

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle
																	, const FGameplayAbilityActorInfo* ActorInfo
																	, const FGameplayTagContainer* SourceTags
																	, const FGameplayTagContainer* TargetTags
																	, FGameplayTagContainer* OptionalRelevantTags)
	const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle
															, const FGameplayAbilityActorInfo* ActorInfo
															, const FGameplayAbilityActivationInfo
															ActivationInfo
															, const FGameplayEventData*
															TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle
														, const FGameplayAbilityActorInfo* ActorInfo
														, const FGameplayAbilityActivationInfo
														ActivationInfo
														, bool bReplicateCancelAbility) override;

private:
	uint8 ComboIndex = 0;
	uint8 MaxCombo = 0;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> GEDamage;

	UFUNCTION()
	void HandleComboNotifyStart(const EHandEquipStatus AttackHand);

	UFUNCTION()
	void HandleComboNotifyEnd(const EHandEquipStatus AttackHand);

	UFUNCTION()
	void Damage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
							, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
							, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	void ClearDelegate();

	TObjectPtr<UPlayMontageWithEvent> Task;

	TObjectPtr<UComboAttackNotifyState> ComboAttackNotifyState;
};
