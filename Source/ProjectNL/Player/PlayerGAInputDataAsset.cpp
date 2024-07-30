// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGAInputDataAsset.h"

UPlayerGAInputDataAsset::UPlayerGAInputDataAsset(const FObjectInitializer& ObjectInitializer)
 : Super(ObjectInitializer)
{
}

const TSet<FGameplayInputAbilityInfo>& UPlayerGAInputDataAsset::GetInputAbilities() const
{
	return InputAbilities;
}

#if WITH_EDITOR
void UPlayerGAInputDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FProperty* Property = PropertyChangedEvent.Property;
	if (Property && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UPlayerGAInputDataAsset, InputAbilities) && !InputAbilities.IsEmpty())
	{
		TArray<FGameplayInputAbilityInfo> InputAbilitiesArray = InputAbilities.Array();
		InputAbilities.Reset();
  
		for (int32 i = 0; i < InputAbilitiesArray.Num(); ++i)
		{
			FGameplayInputAbilityInfo& Info = InputAbilitiesArray[i];
			Info.InputID = i;
			InputAbilities.Add(Info);
		}
	}
}
#endif