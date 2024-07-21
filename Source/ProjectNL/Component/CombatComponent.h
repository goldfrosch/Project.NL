// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackStartNotified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackEndNotified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackTickNotified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatComponentComboAttackInitNotified, UAnimMontage*, CurrentAnim);

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class PROJECTNL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

	FOnCombatComponentComboAttackStartNotified OnNotifiedComboAttackStart;
	FOnCombatComponentComboAttackEndNotified OnNotifiedComboAttackEnd;
	FOnCombatComponentComboAttackTickNotified OnNotifiedComboAttackTick;
	FOnCombatComponentComboAttackInitNotified OnNotifiedComboAttackInit;

	void SetAttackMontages(TArray<UAnimMontage*> Montages);

	UFUNCTION()
	void SetComboDisable();

	UFUNCTION()
	void OnComboBegin();
	
	UFUNCTION()
	void OnComboEnd();

	UFUNCTION()
	void ComboAttack();
	
	uint8 GetComboIndex() const { return ComboIndex; }
	uint8 GetMaxCombo() const { return MaxCombo; }
	
private:
	TArray<TObjectPtr<UAnimMontage>> AttackMontages;
	
	bool IsNextCombo = false;
	uint8 ComboIndex = 0;
	uint8 MaxCombo = 0;
};
