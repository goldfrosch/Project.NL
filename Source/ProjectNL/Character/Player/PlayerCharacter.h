// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerCameraComponent;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class AWeaponBase;

struct FCombatAnimationData;
struct FInputActionValue;

UCLASS()
class PROJECTNL_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter(const class FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ToggleCombatMode();

	UFUNCTION()
	void UnSheathPlayer();
	
	UFUNCTION()
	void SheathPlayer();

	UFUNCTION()
	void SheathingEndPlayer();

	UFUNCTION()
	void UpdateWeaponData();

	UFUNCTION()
	void InitAttack(UAnimMontage* CurrentAnim);

	UFUNCTION()
	void ClearAnimMode();
	
	EPlayerAnimationStatus GetAnimStatus() const { return AnimStatus; }
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	void Move(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void Attack();

	UFUNCTION()
	void OnAttackStart();
	
	UFUNCTION()
	void OnAttackEnd();

	UFUNCTION()
	void OnToggleCamera(EPlayerCameraStatus CameraStatus);
private:
	bool IsThirdCamera = true;
	
	EPlayerAnimationStatus AnimStatus = EPlayerAnimationStatus::Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UPlayerCameraComponent* PlayerCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	bool IsCombatMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleCameraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleCombatAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MainWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SubWeaponAction;

	// TODO: 추후 제거
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> TestWeapon;
};
