// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "UnSheathingEndNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnSheathingEndNotifiedSignature);

UCLASS()
class PROJECTNL_API UUnSheathingEndNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	FOnUnSheathingEndNotifiedSignature OnNotified;
	virtual void Notify(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
