#include "PlayerCameraComponent.h"

#include "GameFramework/SpringArmComponent.h"

UPlayerCameraComponent::UPlayerCameraComponent()
{
	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraSpring->TargetArmLength = CameraZoom;
	CameraSpring->bUsePawnControlRotation = true;
	
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->bUsePawnControlRotation = true;
	
	ThirdFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdFollowCamera"));
	ThirdFollowCamera->bUsePawnControlRotation = false;
}


void UPlayerCameraComponent::ToggleCamera(const FInputActionValue& Value)
{
	if (CameraStatus != EPlayerCameraStatus::First && CameraStatus != EPlayerCameraStatus::Third) return;
	
	if (CameraStatus == EPlayerCameraStatus::Third)
	{
		CameraSpring->TargetArmLength = 0;
		SetFirstPersonView();
		CameraStatus = EPlayerCameraStatus::First;
	} else
	{
		CameraStatus = EPlayerCameraStatus::Third;
		CameraSpring->TargetArmLength = CameraZoom;
		SetThirdPersonView();
	}
	OnPlayerCameraModeChanged.Broadcast(CameraStatus);
}

void UPlayerCameraComponent::SetFirstPersonView()
{
	FirstCamera->SetActive(true);
	ThirdFollowCamera->SetActive(false);
}

void UPlayerCameraComponent::SetThirdPersonView()
{
	FirstCamera->SetActive(false);
	ThirdFollowCamera->SetActive(true);
}