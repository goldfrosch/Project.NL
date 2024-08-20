﻿#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerCameraComponent;
class UInputMappingContext;

UCLASS()
class PROJECTNL_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCameraComponent> PlayerCameraComponent;

protected:
	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
};
