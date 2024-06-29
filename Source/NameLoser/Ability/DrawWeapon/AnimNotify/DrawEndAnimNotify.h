// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DrawEndAnimNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDrawEndNotifiedSignature);
UCLASS()
class NAMELOSER_API UDrawEndAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	FOnDrawEndNotifiedSignature OnNotified;
	virtual void Notify(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
