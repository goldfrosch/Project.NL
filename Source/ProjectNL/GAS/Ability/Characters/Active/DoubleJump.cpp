#include "DoubleJump.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/GAS/Ability/Utility/PlayMontageWithEvent.h"
#include "ProjectNL/Helper/StateHelper.h"

UDoubleJump::UDoubleJump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDoubleJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle
																	, const FGameplayAbilityActorInfo* ActorInfo
																	, const FGameplayAbilityActivationInfo
																	ActivationInfo
																	, const FGameplayEventData* TriggerEventData)
{
	// 해당 조건에 만족하면 Jump 및 Sequence 발동
	// 1. 그냥 아무런 조건 없이 땅에 붙어있는 경우
	// 2. 이미 점프인 상태인 경우
	if (ABaseCharacter* OwnerCharacter = CastChecked<ABaseCharacter>(
		ActorInfo->AvatarActor.Get()))
	{
		if (!OwnerCharacter->GetMovementComponent()->IsFalling())
		{
			OwnerCharacter->Jump();
		}

		else if (FStateHelper::IsPlayerCanDoubleJump(
			GetAbilitySystemComponentFromActorInfo(), OwnerCharacter))
		{
			GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(
				NlGameplayTags::State_Player_Jump);
			GetAbilitySystemComponentFromActorInfo()->AddLooseGameplayTag(
				NlGameplayTags::State_Player_DoubleJump);
			OwnerCharacter->PlayAnimMontage(
				OwnerCharacter->CombatComponent->GetDoubleJumpAnim());
			OwnerCharacter->LaunchCharacter(FVector(0, 0, 400), false, false);
		}
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}
