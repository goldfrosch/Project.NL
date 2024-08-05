#include "PlayerCameraComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectNL/Character/Player/PlayerCharacter.h"

UPlayerCameraComponent::UPlayerCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(
		TEXT("CameraSpring"));
	CameraSpring->TargetArmLength = CameraZoom;
	CameraSpring->bUsePawnControlRotation = true;

	ThirdFollowCamera = CreateDefaultSubobject<UCameraComponent>(
		TEXT("ThirdFollowCamera"));
	ThirdFollowCamera->bUsePawnControlRotation = false;
}

void UPlayerCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType
																					, FActorComponentTickFunction*
																					ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsValid(TargetActor))
	{
		if (const APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner()))
		{
			FVector StartVector = Owner->GetActorLocation();
			StartVector.Z += FixedViewPlusZ;

			const FRotator ViewTo = UKismetMathLibrary::FindLookAtRotation(
				StartVector, TargetActor->GetActorLocation());
			Owner->GetController()->SetControlRotation(ViewTo);
		}
	}
}
