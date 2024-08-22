#include "PlayerControllerBase.h"

#include "PlayerStateBase.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"

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
