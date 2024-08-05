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
		UE_LOG(LogTemp, Display, TEXT("A: %s"), *GetOwner()->GetName());
		if (APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner()))
		{
			const FRotator ViewTo = UKismetMathLibrary::FindLookAtRotation(
				Owner->GetActorLocation(), TargetActor->GetActorLocation());
			Owner->GetController()->SetControlRotation(ViewTo);
		}
	}
}
