#include "PlayerControllerBase.h"

#include "PlayerStateBase.h"
#include "Blueprint/UserWidget.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"
#include "ProjectNL/Widget/MainHUD.h"

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
		CreateMainHUD();
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void APlayerControllerBase::CreateMainHUD()
{
	if (MainHUD)
	{
		return;
	}

	if (!MainHUDClass)
	{
		return;
	}

	if (!IsLocalPlayerController())
	{
		return;
	}

	MainHUD = CreateWidget<UMainHUD>(this, MainHUDClass);
	MainHUD->AddToViewport();
}

void APlayerControllerBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	CreateMainHUD();
}
