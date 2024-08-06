#include "ComboAttack.h"

#include "ProjectNL/Animation/Characters/Attack/ComboAttackNotifyState.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/GAS/Ability/Utility/PlayMontageWithEvent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Weapon/WeaponBase.h"

UComboAttack::UComboAttack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UComboAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle
																			, const FGameplayAbilityActorInfo*
																			ActorInfo
																			, const FGameplayTagContainer* SourceTags
																			, const FGameplayTagContainer* TargetTags
																			, FGameplayTagContainer*
																			OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags
																, OptionalRelevantTags))
	{
		return false;
	}

	return FStateHelper::IsPlayerCombatMode(
		GetAbilitySystemComponentFromActorInfo());
}

void UComboAttack::CancelAbility(const FGameplayAbilitySpecHandle Handle
																, const FGameplayAbilityActorInfo* ActorInfo
																, const FGameplayAbilityActivationInfo
																ActivationInfo, bool bReplicateCancelAbility)
{
	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, NlGameplayTags::State_Player_Attack
																	, NlGameplayTags::State_Player_Idle);
}

void UComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle
																	, const FGameplayAbilityActorInfo* ActorInfo
																	, const FGameplayAbilityActivationInfo
																	ActivationInfo
																	, const FGameplayEventData* TriggerEventData)
{
	if (ABaseCharacter* CurrentCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		if (FStateHelper::IsPlayerJumping(GetAbilitySystemComponentFromActorInfo()))
		{
			// TODO: 점프 상태에서 공격 시 높이에 따라 특수한 공격을 처리하는 것에는 따로 처리할 예정
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo
								, true, false);
			return;
		}

		if (IsValid(Task))
		{
			Task->ExternalCancel();
		}

		const TArray<TObjectPtr<UAnimMontage>> ComboAttack = CurrentCharacter->
			CombatComponent->GetComboAttackAnim();
		MaxCombo = ComboAttack.Num();
		if (!IsValid(ComboAttack[ComboIndex]))
		{
			UE_LOG(LogTemp, Error, TEXT("Fail to Load Combo Animation Try Again"));
			ComboIndex = 0;
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo
								, true, true);
		}

		SetCurrentMontage(ComboAttack[ComboIndex]);

		ComboAttackNotifyState = UAnimNotifyManager::FindNotifyStateByClass<
			UComboAttackNotifyState>(GetCurrentMontage());

		if (IsValid(ComboAttackNotifyState))
		{
			ComboAttackNotifyState->OnNotifiedBegin.Clear();
			ComboAttackNotifyState->OnNotifiedBegin.AddDynamic(
				this, &UComboAttack::HandleComboNotifyStart);
			ComboAttackNotifyState->OnNotifiedEnd.Clear();
			ComboAttackNotifyState->OnNotifiedEnd.AddDynamic(
				this, &UComboAttack::HandleComboNotifyEnd);
		}

		FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																		, NlGameplayTags::State_Player_Idle
																		, NlGameplayTags::State_Player_Attack);
		Task = UPlayMontageWithEvent::InitialEvent(this, NAME_None
																							, GetCurrentMontage()
																							, FGameplayTagContainer());
		Task->OnCancelled.AddDynamic(this, &UComboAttack::OnCancelled);
		Task->OnInterrupted.AddDynamic(this, &UComboAttack::OnCancelled);
		Task->OnBlendOut.AddDynamic(this, &UComboAttack::OnCancelled);
		Task->OnCompleted.AddDynamic(this, &UComboAttack::OnCompleted);
		Task->ReadyForActivation();
	}
}

void UComboAttack::HandleComboNotifyStart()
{
	ABaseCharacter* AvatarCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo());

	AvatarCharacter->CombatComponent->GetMainWeapon()->SetWeaponDamageable();
	AvatarCharacter->CombatComponent->GetMainWeapon()->OnNotifiedAttack.
									AddDynamic(this, &UComboAttack::Damage);

	// 어차피 ComboAttack 자체가 무기를 뽑지 않은 Combat 상태가 아니기 때문에
	// MainWeapon은 따로 검증하지 않는다.
	if (IsValid(AvatarCharacter->CombatComponent->GetSubWeapon()))
	{
		AvatarCharacter->CombatComponent->GetSubWeapon()->SetWeaponDamageable();
		AvatarCharacter->CombatComponent->GetSubWeapon()->OnNotifiedAttack.
										AddDynamic(this, &UComboAttack::Damage);
	}
}

void UComboAttack::HandleComboNotifyEnd()
{
	ComboIndex = ComboIndex == MaxCombo - 1 ? 0 : ComboIndex + 1;
	FStateHelper::ChangePlayerState(GetAbilitySystemComponentFromActorInfo()
																	, NlGameplayTags::State_Player_Attack
																	, NlGameplayTags::State_Player_Idle);
	ABaseCharacter* AvatarCharacter = Cast<ABaseCharacter>(
		GetAvatarActorFromActorInfo());

	AvatarCharacter->CombatComponent->GetMainWeapon()->UnsetWeaponDamageable();
	AvatarCharacter->CombatComponent->GetMainWeapon()->OnNotifiedAttack.Clear();

	if (IsValid(AvatarCharacter->CombatComponent->GetSubWeapon()))
	{
		AvatarCharacter->CombatComponent->GetSubWeapon()->UnsetWeaponDamageable();
		AvatarCharacter->CombatComponent->GetSubWeapon()->OnNotifiedAttack.Clear();
	}
}

void UComboAttack::OnCompleted(FGameplayTag EventTag
															, FGameplayEventData EventData)
{
	ClearDelegate();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
						, false);
}

void UComboAttack::OnCancelled(FGameplayTag EventTag
															, FGameplayEventData EventData)
{
	ClearDelegate();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
						, false);
}

void UComboAttack::Damage(UPrimitiveComponent* OverlappedComponent
													, AActor* OtherActor, UPrimitiveComponent* OtherComp
													, int32 OtherBodyIndex, bool bFromSweep
													, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("TEST: %d"), OtherBodyIndex);
}

void UComboAttack::ClearDelegate()
{
	if (ComboAttackNotifyState)
	{
		ComboAttackNotifyState->OnNotifiedBegin.RemoveAll(this);
		ComboAttackNotifyState->OnNotifiedEnd.RemoveAll(this);
	}
}
