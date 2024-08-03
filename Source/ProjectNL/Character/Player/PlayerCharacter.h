// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerGAInputDataAsset;
class UPlayerCameraComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
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
	void InitPlayerWeapon();

	FORCEINLINE UPlayerGAInputDataAsset*
	GetPlayerGameplayAbilitiesDataAsset() const { return PlayerGAInputDataAsset; }

protected:
	virtual void BeginPlay() override;

	virtual void
	SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	bool IsThirdCamera = true;

	void InitAbilitySystem();
	void OnAbilityInputPressed(const int32 InputID);
	void OnAbilityInputReleased(const int32 InputID);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action
		, meta = (AllowPrivateAccess = "true"))
	UPlayerCameraComponent* PlayerCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action
		, meta = (AllowPrivateAccess = "true"))
	bool IsCombatMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySystem"
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerGAInputDataAsset> PlayerGAInputDataAsset;

	// TODO: 추후 제거
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon
		, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> TestWeapon;
};
