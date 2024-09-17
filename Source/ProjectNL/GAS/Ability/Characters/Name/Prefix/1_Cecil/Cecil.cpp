#include "Cecil.h"

#include "AbilitySystemComponent.h"
#include "ProjectNL/Character/Player/PlayerCharacter.h"
#include "ProjectNL/Component/PlayerCameraComponent.h"
#include "ProjectNL/Helper/GameplayTagsHelper.h"

UCecil::UCecil()
{
	RepeatTime = -1;
}

void UCecil::OnActivateAbility()
{
	if (GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(
		NlGameplayTags::Name_Prefix_Cecil))
	{
		return;
	}
	GetAbilitySystemComponentFromActorInfo()->SetLooseGameplayTagCount(
		NlGameplayTags::Name_Prefix_Cecil, 1);

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(
		GetAvatarActorFromActorInfo()))
	{
		// Post Process Volume 변경 및 추가
		// TODO: 이후 공통 함수로 이전해도 무방할 로직으로 보임
		TArray<FWeightedBlendable>* PlayerRenderPostProcess = &Player->
			PlayerCameraComponent->ThirdFollowCamera->PostProcessSettings.
			WeightedBlendables.Array;
		if (PlayerRenderPostProcess->Num() > 0)
		{
			PlayerRenderPostProcess->Empty();
		}

		FWeightedBlendable* NewBlend = new FWeightedBlendable();
		NewBlend->Object = UMaterialInstanceDynamic::Create(
			PostProcessMaterial, this);
		NewBlend->Weight = 1;

		PlayerRenderPostProcess->Add(*NewBlend);
	}
	// Gameplay Effect 부여
	if (IsValid(BuffEffect))
	{
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectToSelf(
			BuffEffect.GetDefaultObject(), 1
			, GetAbilitySystemComponentFromActorInfo()->MakeEffectContext());
	}
}
