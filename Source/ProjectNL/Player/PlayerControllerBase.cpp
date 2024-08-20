// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "PlayerStateBase.h"
#include "ProjectNL/Character/BaseCharacter.h"

void APlayerControllerBase::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(P))
	{
		// 컨트롤러에서 빙의된 폰이 base character 일 경우에 대해서
		// OwnerActor와 AvatarActor를 동일한 결과로 기본 값을 세팅한다.
		BaseCharacter->GetAbilitySystemComponent()->InitAbilityActorInfo(
			BaseCharacter, BaseCharacter);
	}
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	// 커맨드 입력으로 GAS의 디버그 화면 노출
	ConsoleCommand(TEXT("showdebug abilitysystem"));
}

void APlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (APlayerStateBase* PS = GetPlayerState<APlayerStateBase>())
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void APlayerControllerBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}
