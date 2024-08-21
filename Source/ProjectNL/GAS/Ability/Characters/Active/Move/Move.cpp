// Fill out your copyright notice in the Description page of Project Settings.


#include "Move.h"

#include "AbilitySystemComponent.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/MovementManager.h"

UMove::UMove(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMove::ActivateAbility(const FGameplayAbilitySpecHandle Handle
														, const FGameplayAbilityActorInfo* ActorInfo
														, const FGameplayAbilityActivationInfo
														ActivationInfo
														, const FGameplayEventData* TriggerEventData)
{
	if (FStateHelper::IsPlayerIdle(GetAbilitySystemComponentFromActorInfo()))
	{
		const FVector2D MovementVector = InputValue->GetValue().Get<FVector2D>();
		UE_LOG(LogTemp, Display, TEXT("테스트 Move Data: %f, %f"), MovementVector.X
					, MovementVector.Y);
		UMovementManager::Move(Cast<APawn>(GetAvatarActorFromActorInfo())
													, MovementVector);
	}
}
