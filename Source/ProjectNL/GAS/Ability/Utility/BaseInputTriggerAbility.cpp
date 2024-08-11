#include "BaseInputTriggerAbility.h"

#include "EnhancedInputComponent.h"
#include "ProjectNL/Character/Player/PlayerCharacter.h"
#include "ProjectNL/Player/PlayerGAInputDataAsset.h"

UBaseInputTriggerAbility::UBaseInputTriggerAbility(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bCancelAbilityOnInputReleased(false)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UBaseInputTriggerAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo
	, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bool bSuccess = false;

	if (const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		EnhancedInputComponent = Cast<UEnhancedInputComponent>(
			PlayerCharacter->InputComponent);
		if (EnhancedInputComponent)
		{
			if (const UPlayerGAInputDataAsset* PlayerGameplayAbilitiesDataAsset =
				PlayerCharacter->GetPlayerGameplayAbilitiesDataAsset())
			{
				const TSet<FGameplayInputAbilityInfo>& InputAbilities =
					PlayerGameplayAbilitiesDataAsset->GetInputAbilities();
				for (const auto& It : InputAbilities)
				{
					if (It.IsValid() && It.GameplayAbilityClass == GetClass())
					{
						const FEnhancedInputActionEventBinding& TriggeredEventBinding =
							EnhancedInputComponent->BindAction(
								It.InputAction, ETriggerEvent::Triggered, this
								, &UBaseInputTriggerAbility::OnTriggeredInputAction);
						const uint32 TriggeredEventHandle = TriggeredEventBinding.
							GetHandle();

						TriggeredEventHandles.AddUnique(TriggeredEventHandle);

						bSuccess = true;
					}
				}
			}
		}
	}
	else
	{
		// 대상이 Player가 아닌 경우는 Input 탐색 대상이 아닌 것으로 인지해
		// 설정을 true로 변경해 그대로 GA를 통과시킨다.
		bSuccess = true;
	}

	if (bSuccess)
	{
		CommitAbility(Handle, ActorInfo, ActivationInfo);
	}
	else
	{
		constexpr bool bReplicateCancelAbility = true;
		CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	}
}

void UBaseInputTriggerAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo
	, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility
										, bWasCancelled);

	if (EnhancedInputComponent)
	{
		for (const uint32 EventHandle : TriggeredEventHandles)
		{
			EnhancedInputComponent->RemoveBindingByHandle(EventHandle);
		}

		EnhancedInputComponent = nullptr;
	}

	TriggeredEventHandles.Reset();
}

void UBaseInputTriggerAbility::InputReleased(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	if (bCancelAbilityOnInputReleased)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UBaseInputTriggerAbility::OnTriggeredInputAction(
	const FInputActionValue& Value)
{
}
