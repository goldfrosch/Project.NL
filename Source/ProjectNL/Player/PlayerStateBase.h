#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"
#include "PlayerStateBase.generated.h"

UCLASS()
class PROJECTNL_API APlayerStateBase
	: public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerStateBase();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ability System")
	UNLAbilitySystemComponent* AbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
