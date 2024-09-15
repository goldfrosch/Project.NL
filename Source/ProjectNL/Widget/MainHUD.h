#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MainHUD.generated.h"

class UProgressBar;
struct FOnAttributeChangeData;

UCLASS()
class PROJECTNL_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UProgressBar> HealthBar;

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	float CurrentHealth;

	UPROPERTY()
	float MaxHealth;

	void HandleCurrentHealthChanged(const FOnAttributeChangeData& Data);
	// void HandleMaxHealthChanged();
};
