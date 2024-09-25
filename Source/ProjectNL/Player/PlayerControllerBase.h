#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"


class UMainHUD;

UCLASS()
class PROJECTNL_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void BeginPlayingState() override;

	void CreateMainHUD();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UMainHUD> MainHUDClass;

	TObjectPtr<UMainHUD> MainHUD;
};
