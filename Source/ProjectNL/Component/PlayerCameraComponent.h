// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "PlayerCameraComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCameraModeChanged, EPlayerCameraStatus, CameraStatus);

enum class EPlayerCameraStatus : uint8;
struct FInputActionValue;
class USpringArmComponent;

UCLASS()
class PROJECTNL_API UPlayerCameraComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPlayerCameraComponent();
	
	void SetThirdPersonView();
	void SetFirstPersonView();
	
	void ToggleCamera(const FInputActionValue& Value);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraSpring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FirstCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* ThirdFollowCamera;

	FOnPlayerCameraModeChanged OnPlayerCameraModeChanged;

	float GetCameraZoom() const { return CameraZoom; }
private:
	EPlayerCameraStatus CameraStatus = EPlayerCameraStatus::Third;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	float CameraZoom = 300.f;
	
};
