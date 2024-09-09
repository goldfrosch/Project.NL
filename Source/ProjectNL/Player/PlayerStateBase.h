#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"
#include "PlayerStateBase.generated.h"

class UPlayerAttributeSet;

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

protected:
	virtual void BeginPlay() override;

private:
	void MovementSpeedChanged(const FOnAttributeChangeData& Data);
};
