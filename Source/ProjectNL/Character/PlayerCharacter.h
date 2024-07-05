// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

// class AWeaponBase;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

struct FInputActionValue;

UENUM()
enum EPlayerAnimationStatus
{
	Default,
	Drawing,
	Sheathing,
	Attacking
};

UCLASS()
class PROJECTNL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ToggleCombatMode();
	
	// UFUNCTION()
	// void DrawWeaponMontageNotifyBegin();

	UFUNCTION()
	void ToggleCombatWeaponMontageNotifyEnd();

	// UFUNCTION()
	// void SheathingEndWeaponMontageNotify();

	// UFUNCTION()
	// void InitWeaponDrawRightBind(class UDrawAnimNotify* DrawNotify);
	//
	// UFUNCTION()
	// void InitWeaponDrawEndRightBind(class UDrawEndAnimNotify* DrawEndNotify);
	//
	// UFUNCTION()
	// void InitWeaponSheathingEndRightBind(class USheathingEndAnimNotify* SheathingEndNotify);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ScrollClose(const FInputActionValue& Value);

	void SetThirdPersonView();
	void SetFirstPersonView();
	// 1인칭인지 아닌지 검증하는 로직
	bool GetIsFirstPersonView() const;
	

private:
	const uint8 PercentCameraMovement = 5;
	const uint8 MaxCameraScroll = 150;
	const uint8 MaxCountForChangeThirdPerson = 10;

	// 카메라의 인칭을 커스텀하게 잡아주는 float value
	// N번만큼 스크롤할 때 3인칭으로 전환하게 해주는 value다.
	uint8 CountForChangeThirdPerson = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	bool IsCombatMode = false;

	EPlayerAnimationStatus AnimStatus = Default;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdFollowCamera;

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
	UInputAction* ScrollCloseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DrawWeaponAction;

	// UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// AWeaponBase* RightWeaponData;
	//
	// // 임시 객체로 자연스러운 데이터 로드 or 아이템 줍기 기능 추가 시 제거될 property
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	// TSubclassOf<AWeaponBase> RightWeapon;
};
