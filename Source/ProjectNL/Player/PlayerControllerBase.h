#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"


UCLASS()
class PROJECTNL_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
};
