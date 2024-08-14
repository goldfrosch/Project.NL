// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerGAInputDataAsset;
class UPlayerCameraComponent;
class UCameraComponent;
class UGameplayEffect;
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
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UPlayerGAInputDataAsset*
	GetPlayerGameplayAbilitiesDataAsset() const { return PlayerGAInputDataAsset; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCameraComponent> PlayerCameraComponent;

protected:
	virtual void BeginPlay() override;

	virtual void
	SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	bool IsThirdCamera = true;
	UPROPERTY(Replicated)
	bool IsInputBound = false;

	void InitAbilitySystem();
	void OnAbilityInputPressed(const int32 InputID);
	void OnAbilityInputReleased(const int32 InputID);

	void InitTag();

	void BindAbility();

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
};
