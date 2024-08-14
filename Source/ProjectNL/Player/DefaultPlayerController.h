﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

UCLASS()
class PROJECTNL_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void AcknowledgePossession(APawn* P) override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;
};
