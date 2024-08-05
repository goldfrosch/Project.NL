// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleFixedCamera.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectNL/Character/Player/PlayerCharacter.h"
#include "ProjectNL/Component/PlayerCameraComponent.h"

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
		FVector EndVector = UKismetMathLibrary::GetForwardVector(
			PlayerActor->GetControlRotation()) * 50;
		TArray<AActor*> ActorsToNotTargeting;
		ActorsToNotTargeting.Add(PlayerActor);
		FHitResult OutHit;

		if (UKismetSystemLibrary::SphereTraceSingleForObjects(
			GetWorld(), StartVector, EndVector, 350.f, ObjectTypesArray, false
			, ActorsToNotTargeting, EDrawDebugTrace::ForDuration, OutHit, true))
		{
			if (OutHit.GetActor() == PlayerActor->PlayerCameraComponent->
																						GetTargetActor())
			{
				PlayerActor->PlayerCameraComponent->SetTargetActor(nullptr);
			}
			else
			{
				PlayerActor->PlayerCameraComponent->SetTargetActor(OutHit.GetActor());
			}
		}
		else
		{
			PlayerActor->PlayerCameraComponent->SetTargetActor(nullptr);
		}

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
							, false);
	}
}
