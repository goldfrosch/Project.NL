// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EquipEndNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipEndNotifiedSignature);

UCLASS()
class PROJECTNL_API UEquipEndNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnEquipEndNotifiedSignature OnNotified;

	virtual void Notify(USkeletalMeshComponent* MeshComp
											, UAnimSequenceBase* Animation
											, const FAnimNotifyEventReference&
											EventReference) override
	{
		OnNotified.Broadcast();
		Super::Notify(MeshComp, Animation, EventReference);
		OnNotified.Clear();
	}
};
