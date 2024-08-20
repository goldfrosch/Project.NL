#include "Look.h"

#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

ULook::ULook(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULook::OnTriggeredInputAction(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	APawn* AvatarActor = Cast<APawn>(GetAvatarActorFromActorInfo());

	if (AvatarActor->Controller != nullptr)
	{
		const float NewPitch = LookAxisVector.Y *
			UGameplayStatics::GetWorldDeltaSeconds(this) * 60.f;
		const float NewYaw = LookAxisVector.X *
			UGameplayStatics::GetWorldDeltaSeconds(this) * 60.f;

		AvatarActor->AddControllerYawInput(NewYaw);
		AvatarActor->AddControllerPitchInput(NewPitch);
	}
}
