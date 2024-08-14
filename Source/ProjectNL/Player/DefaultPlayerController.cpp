// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"

#include "AbilitySystemComponent.h"
#include "DefaultPlayerState.h"
#include "ProjectNL/Character/BaseCharacter.h"

void ADefaultPlayerController::AcknowledgePossession(APawn* P)
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

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// 커맨드 입력으로 GAS의 디버그 화면 노출
	ConsoleCommand(TEXT("showdebug abilitysystem"));
}

void ADefaultPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ADefaultPlayerState* PS = GetPlayerState<ADefaultPlayerState>())
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void ADefaultPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}
