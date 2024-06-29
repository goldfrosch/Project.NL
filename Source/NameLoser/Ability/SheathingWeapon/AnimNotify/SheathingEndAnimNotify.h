// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SheathingEndAnimNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSheathingEndNotifiedSignature);
UCLASS()
class NAMELOSER_API USheathingEndAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	FOnSheathingEndNotifiedSignature OnNotified;
	virtual void Notify(
		USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
