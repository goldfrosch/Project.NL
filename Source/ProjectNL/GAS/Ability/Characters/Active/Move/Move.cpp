// Fill out your copyright notice in the Description page of Project Settings.


#include "Move.h"

#include "AbilitySystemComponent.h"
#include "InputActionValue.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/MovementManager.h"

UMove::UMove(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMove::OnTriggeredInputAction(const FInputActionValue& Value)
{
	if (FStateHelper::IsPlayerIdle(GetAbilitySystemComponentFromActorInfo()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		UMovementManager::Move(Cast<APawn>(GetAvatarActorFromActorInfo())
													, MovementVector);
	}
}
