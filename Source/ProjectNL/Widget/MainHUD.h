#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MainHUD.generated.h"

class UProgressBar;
struct FOnAttributeChangeData;

enum class EMainHUDProgressBarType
{
	Health, Mana, Stamina
};

UCLASS()
class PROJECTNL_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY()
	TObjectPtr<UProgressBar> ManaBar;

	UPROPERTY()
	TObjectPtr<UProgressBar> StaminaBar;

protected:
	virtual void NativeConstruct() override;

private:
	float BarIncreasePercent = 0.002;

	const float DefaultMaxPercentValue = 100;

	float GetProgressBarStartPosX(const float PlusValue
																, const EMainHUDProgressBarType Type) const;
	void InitializeProgressBar(TObjectPtr<UProgressBar> HUDProgressBar
														, const EMainHUDProgressBarType Type
														, const float CurrentValue, const float MaxValue);

	void SetProgressBarPercent(TObjectPtr<UProgressBar> HUDProgressBar
														, float Percent) const;

	void SetProgressBarTransform(TObjectPtr<UProgressBar> HUDProgressBar
															, const EMainHUDProgressBarType Type
															, const float MaxValue) const;

	float CurrentHealth;
	float MaxHealth;

	void HandleCurrentHealthChanged(const FOnAttributeChangeData& Data);
	void HandleMaxHealthChanged(const FOnAttributeChangeData& Data);

	float CurrentMana;
	float MaxMana;

	void HandleCurrentManaChanged(const FOnAttributeChangeData& Data);
	void HandleMaxManaChanged(const FOnAttributeChangeData& Data);

	float CurrentStamina;
	float MaxStamina;

	void HandleCurrentStaminaChanged(const FOnAttributeChangeData& Data);
	void HandleMaxStaminaChanged(const FOnAttributeChangeData& Data);
};
