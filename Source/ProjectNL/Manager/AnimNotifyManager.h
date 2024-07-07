// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AnimNotifyManager.generated.h"

UCLASS()
class PROJECTNL_API UAnimNotifyManager : public UObject
{
	GENERATED_BODY()
public:
	template<typename AnimNotify>
	UFUNCTION() static TObjectPtr<AnimNotify> FindNotifyByClass(const TObjectPtr<UAnimMontage> Animation)
	{
		if (!Animation)
		{
			return nullptr;
		}

		for (FAnimNotifyEvent NotifyEvent : Animation->Notifies)
		{
			if (const auto AnimationNotify = Cast<AnimNotify>(NotifyEvent.Notify))
			{
				return AnimationNotify;
			}
		}

		return nullptr;
	}
};