#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/GAS/Ability/Utility/BaseInputTriggerAbility.h"
#include "Move.generated.h"

UCLASS()
class PROJECTNL_API UMove : public UBaseInputTriggerAbility
{
	GENERATED_BODY()

public:
	UMove(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnTriggeredInputAction(const FInputActionValue& Value) override;
};
