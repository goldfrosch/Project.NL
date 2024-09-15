﻿#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SwapTwoHandWeaponNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwapWeaponNotifiedSignature);

UCLASS()
class PROJECTNL_API USwapTwoHandWeaponNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnSwapWeaponNotifiedSignature OnNotified;

	virtual void Notify(USkeletalMeshComponent* MeshComp
											, UAnimSequenceBase* Animation
											, const FAnimNotifyEventReference&
											EventReference) override
	{
		OnNotified.Broadcast();
		Super::Notify(MeshComp, Animation, EventReference);
	}
};
