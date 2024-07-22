// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ComboAttackStartNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboAttackStartNotifiedSignature);

UCLASS()
class PROJECTNL_API UComboAttackStartNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	FOnComboAttackStartNotifiedSignature OnNotified;
	virtual void Notify(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override {
		OnNotified.Broadcast();
		Super::Notify(MeshComp, Animation, EventReference);
	}
};
