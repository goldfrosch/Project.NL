// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackStartNotified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackEndNotified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatComponentComboAttackTickNotified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatComponentComboAttackInitNotified, UAnimMontage*, CurrentAnim);

class AWeaponBase;

UCLASS()
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

	UFUNCTION()
	void UpdateWeaponData();

	TObjectPtr<UAnimMontage> GetUnSheathAnimMontage() const { return UnSheathingAnimMontage; }
	TObjectPtr<UAnimMontage> GetSheathAnimMontage() const { return SheathingAnimMontage; }

	AWeaponBase* GetMainWeapon() const { return MainWeapon; }
	AWeaponBase* GetSubWeapon() const { return SubWeapon; }
	void SetMainWeapon(AWeaponBase* NewWeapon) { MainWeapon = NewWeapon; }
	void SetSubWeapon(AWeaponBase* NewWeapon) { SubWeapon = NewWeapon; }
	
	uint8 GetComboIndex() const { return ComboIndex; }
	uint8 GetMaxCombo() const { return MaxCombo; }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle CombatAnimData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* MainWeapon;
  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* SubWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> AttackMontages;
	
	UPROPERTY(EditDefaultsOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> SheathingAnimMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> UnSheathingAnimMontage;
	
	bool IsNextCombo = false;
	uint8 ComboIndex = 0;
	uint8 MaxCombo = 0;
};
