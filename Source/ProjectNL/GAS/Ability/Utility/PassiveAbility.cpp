#include "PassiveAbility.h"

UPassiveAbility::UPassiveAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UPassiveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle
																			, const FGameplayAbilityActorInfo*
																			ActorInfo
																			, const FGameplayAbilityActivationInfo
																			ActivationInfo
																			, const FGameplayEventData*
																			TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 원래 로직상 RepeatTime이 -1인 경우에만 한번 실행하는 로직으로 설정하지만, 혹시 모를 예외 상황 방지를 위해
	// 0보다 작거나 같은 경우는 한번 실행으로 로직을 처리한다.
	if (RepeatTime <= 0)
	{
		OnActivateAbility();
	}
	else
	{
		ActorInfo->AvatarActor->GetWorldTimerManager().SetTimer(
			PassiveTimerHandle, this, &ThisClass::OnActivateAbility, RepeatTime
			, true);
	}
}

void UPassiveAbility::OnActivateAbility()
{
}
