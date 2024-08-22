#include "BaseInputTriggerAbility.h"

#include "AbilitySystemComponent.h"

UBaseInputTriggerAbility::UBaseInputTriggerAbility(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UBaseInputTriggerAbility::OnAvatarSet(
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	SetupEnhancedInputBindings(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UBaseInputTriggerAbility::SetupEnhancedInputBindings(
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (IsValid(ActorInfo->AvatarActor.Get()))
	{
		if (const APawn* AvatarPawn = Cast<APawn>(ActorInfo->AvatarActor.Get()))
		{
			if (const AController* PawnController = AvatarPawn->GetController())
			{
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<
					UEnhancedInputComponent>(PawnController->InputComponent.Get()))
				{
					if (UBaseInputTriggerAbility* AbilityInstance = Cast<
						UBaseInputTriggerAbility>(Spec.Ability))
					{
						if (IsValid(AbilityInstance->ActivationInputAction))
						{
							if (InputPressedTriggerType != ETriggerEvent::None)
							{
								EnhancedInputComponent->BindAction(
									AbilityInstance->ActivationInputAction
									, AbilityInstance->InputPressedTriggerType, AbilityInstance
									, &ThisClass::HandleInputPressedEvent, ActorInfo
									, Spec.Handle);
							}

							if (InputReleasedTriggerType != ETriggerEvent::None)
							{
								EnhancedInputComponent->BindAction(
									AbilityInstance->ActivationInputAction
									, AbilityInstance->InputReleasedTriggerType, AbilityInstance
									, &ThisClass::HandleInputReleasedEvent, ActorInfo
									, Spec.Handle);
							}
						}
					}
				}
			}
		}
	}
}

void UBaseInputTriggerAbility::HandleInputTriggerInputEvent(
	const FInputActionValue& Value)
{
}


void UBaseInputTriggerAbility::HandleInputPressedEvent(
	const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilitySpecHandle SpecHandle)
{
	if (FGameplayAbilitySpec* Spec = ActorInfo->AbilitySystemComponent->
																							FindAbilitySpecFromHandle(
																								SpecHandle))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->
			AbilitySystemComponent.Get())
		{
			Spec->InputPressed = true;

			if (Spec->IsActive())
			{
				if (Spec->Ability.Get()->bReplicateInputDirectly && !
					AbilitySystemComponent->IsOwnerActorAuthoritative())
				{
					AbilitySystemComponent->ServerSetInputPressed(
						Spec->Ability.Get()->GetCurrentAbilitySpecHandle());
				}
				AbilitySystemComponent->AbilitySpecInputPressed(*Spec);
				AbilitySystemComponent->InvokeReplicatedEvent(
					EAbilityGenericReplicatedEvent::InputPressed, Spec->Handle
					, Spec->ActivationInfo.GetActivationPredictionKey());
			}
			else
			{
				AbilitySystemComponent->TryActivateAbility(SpecHandle);
			}
		}
	}
}

void UBaseInputTriggerAbility::HandleInputReleasedEvent(
	const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilitySpecHandle SpecHandle)
{
	if (FGameplayAbilitySpec* Spec = ActorInfo->AbilitySystemComponent->
																							FindAbilitySpecFromHandle(
																								SpecHandle))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->
			AbilitySystemComponent.Get())
		{
			Spec->InputPressed = false;

			if (Spec->IsActive())
			{
				if (Spec->Ability.Get()->bReplicateInputDirectly && !
					AbilitySystemComponent->IsOwnerActorAuthoritative())
				{
					AbilitySystemComponent->ServerSetInputReleased(SpecHandle);
				}
				AbilitySystemComponent->AbilitySpecInputPressed(*Spec);
				AbilitySystemComponent->InvokeReplicatedEvent(
					EAbilityGenericReplicatedEvent::InputReleased, SpecHandle
					, Spec->ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UBaseInputTriggerAbility::OnRemoveAbility(
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (IsValid(ActorInfo->AvatarActor.Get()))
	{
		if (const APawn* AvatarPawn = Cast<APawn>(ActorInfo->AvatarActor.Get()))
		{
			if (const AController* PawnController = AvatarPawn->GetController())
			{
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<
					UEnhancedInputComponent>(PawnController->InputComponent))
				{
					EnhancedInputComponent->ClearBindingsForObject(Spec.Ability.Get());
				}
			}
		}
	}

	Super::OnRemoveAbility(ActorInfo, Spec);
}
