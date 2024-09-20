#include "PlayerControllerBase.h"

#include "Blueprint/UserWidget.h"
#include "ProjectNL/Widget/MainHUD.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	// 커맨드 입력으로 GAS의 디버그 화면 노출
	ConsoleCommand(TEXT("showdebug abilitysystem"));
	CreateMainHUD();
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
