// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"

#include "AbilitySystemComponent.h"
#include "ProjectNL/Character/BaseCharacter.h"

void ADefaultPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(P))
	{
		// 컨트롤러에서 빙의된 폰이 base character 일 경우에 대해서
		// OwnerActor와 AvatarActor를 동일한 결과로 기본 값을 세팅한다.
		BaseCharacter->GetAbilitySystemComponent()
		->InitAbilityActorInfo(BaseCharacter, BaseCharacter);
	}
}
