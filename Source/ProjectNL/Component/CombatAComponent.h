// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatAComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackStartNotified);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackEndNotified);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackTickNotified);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnCombatComponentComboAttackInitNotified, UAnimMontage*, CurrentAnim);

class AWeaponBase;

UCLASS()
class PROJECTNL_API UCombatAComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatAComponent();

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

	UFUNCTION()
	void UpdateWeaponData();

	FORCEINLINE TObjectPtr<UAnimMontage> GetUnEquipAnimMontage() const
	{
		return UnEquipAnimMontage;
	}

	FORCEINLINE TObjectPtr<UAnimMontage> GetEquipAnimMontage() const
	{
		return EquipAnimMontage;
	}

	FORCEINLINE AWeaponBase* GetMainWeapon() const { return MainWeapon; }
	FORCEINLINE AWeaponBase* GetSubWeapon() const { return SubWeapon; }
	FORCEINLINE void SetMainWeapon(AWeaponBase* NewWeapon)
	{
		MainWeapon = NewWeapon;
	}

	FORCEINLINE void SetSubWeapon(AWeaponBase* NewWeapon)
	{
		SubWeapon = NewWeapon;
	}

	FORCEINLINE uint8 GetComboIndex() const { return ComboIndex; }
	FORCEINLINE uint8 GetMaxCombo() const { return MaxCombo; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle CombatAnimData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon
		, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* MainWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon
		, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* SubWeapon;

	UPROPERTY()
	TArray<TObjectPtr<UAnimMontage>> AttackMontages;

	UPROPERTY()
	TObjectPtr<UAnimMontage> EquipAnimMontage;

	UPROPERTY()
	TObjectPtr<UAnimMontage> UnEquipAnimMontage;

	bool IsNextCombo = false;
	uint8 ComboIndex = 0;
	uint8 MaxCombo = 0;
};
