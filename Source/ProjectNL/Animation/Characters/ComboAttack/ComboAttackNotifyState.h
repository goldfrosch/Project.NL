// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ComboAttackNotifyState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboAttackNotifiedBeginSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboAttackNotifiedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboAttackNotifiedEndSignature);

UCLASS()
class PROJECTNL_API UComboAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	FOnComboAttackNotifiedSignature OnNotifiedTick;
	FOnComboAttackNotifiedEndSignature OnNotifiedEnd;
	FOnComboAttackNotifiedBeginSignature OnNotifiedBegin;
	
	virtual void NotifyTick(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override
	{
		OnNotifiedTick.Broadcast();
		Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	}

	virtual void NotifyEnd(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override
	{
		OnNotifiedEnd.Broadcast();
		Super::NotifyEnd(MeshComp, Animation, EventReference);
	}

	virtual void NotifyBegin(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float TotalDuration, const FAnimNotifyEventReference& EventReference) override
	{
		OnNotifiedBegin.Broadcast();
		Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	}
};
