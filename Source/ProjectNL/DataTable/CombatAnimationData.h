// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "CombatAnimationData.generated.h"

USTRUCT(BlueprintType)
struct  PROJECTNL_API FCombatAnimationData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAnimationType AnimationType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EUWeaponType MainWeaponType;

	// 메인 무기가 양손이면 sub가 필요없고, 한손이면 자동으로 sub도 한손이 되기 때문에 main만 기준으로 삼음
	// 추가로 서브 무기의 유무는 SubWeaponType으로 결정하는 것이 좋아보임
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EUEquippedHandType MainWeaponHandType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EUWeaponType SubWeaponType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UAnimMontage*> AnimGroup;
};
