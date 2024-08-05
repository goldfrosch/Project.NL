// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleFixedCamera.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectNL/Character/Player/PlayerCharacter.h"
#include "ProjectNL/Component/PlayerCameraComponent.h"
#include "ProjectNL/Component/WidgetsComponent.h"

UToggleFixedCamera::UToggleFixedCamera(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UToggleFixedCamera::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayTagContainer* SourceTags
	, const FGameplayTagContainer* TargetTags
	, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags
																, OptionalRelevantTags)) { return false; }
	return true;
}


void UToggleFixedCamera::ActivateAbility(const FGameplayAbilitySpecHandle Handle
																				, const FGameplayAbilityActorInfo*
																				ActorInfo
																				, const FGameplayAbilityActivationInfo
																				ActivationInfo
																				, const FGameplayEventData*
																				TriggerEventData)
{
	if (TObjectPtr<APlayerCharacter> PlayerActor = Cast<APlayerCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		const FVector StartVector = PlayerActor->GetActorLocation();

		constexpr float EndVectorDistance = 5000;
		FVector EndVector = PlayerActor->GetActorLocation() +
			UKismetMathLibrary::GetForwardVector(PlayerActor->GetControlRotation()) *
			EndVectorDistance;

		TArray<AActor*> ActorsToNotTargeting;
		ActorsToNotTargeting.Add(PlayerActor);
		FHitResult OutHit;

		if (UKismetSystemLibrary::SphereTraceSingleForObjects(
			GetWorld(), StartVector, EndVector, 350.f, ObjectTypesArray, false
			, ActorsToNotTargeting, EDrawDebugTrace::None, OutHit, true))
		{
			if (OutHit.GetActor() == PlayerActor->PlayerCameraComponent->
																						GetTargetActor())
			{
				ToggleFixedViewWidget(PlayerActor, OutHit.GetActor(), false);
			}
			else
			{
				ToggleFixedViewWidget(PlayerActor, OutHit.GetActor(), true);
			}
		}
		else
		{
			ToggleFixedViewWidget(PlayerActor, OutHit.GetActor(), false);
		}

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
							, false);
	}
}

void UToggleFixedCamera::ToggleFixedViewWidget(APlayerCharacter* Player
																							, AActor* Target
																							, const bool IsActive)
{
	// TODO: 추후 위젯 관련은 BasePawn으로 이전 예정
	if (ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(Target))
	{
		TargetCharacter->WidgetsComponent->ToggleFixedViewWidget(IsActive);
	}

	if (IsActive)
	{
		Player->PlayerCameraComponent->SetTargetActor(Target);
		Player->bUseControllerRotationYaw = true;
		return;
	}
	Player->PlayerCameraComponent->SetTargetActor(nullptr);
	Player->bUseControllerRotationYaw = false;
}
