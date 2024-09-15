#include "MainHUD.h"

#include "ProjectNL/GAS/Attribute/PlayerAttributeSet.h"
#include "ProjectNL/Player/PlayerStateBase.h"


void UMainHUD::NativeConstruct()
{
	const TObjectPtr<APlayerStateBase> PlayerState = Cast<APlayerStateBase>(
		GetOwningPlayer()->PlayerState);

	if (IsValid(PlayerState))
	{
		if (UNLAbilitySystemComponent* AbilitySystemComponent = PlayerState->
			AbilitySystemComponent)
		{
			if (const UPlayerAttributeSet* PlayerAttributeSet = Cast<
				UPlayerAttributeSet>(AbilitySystemComponent->AttributeSet))
			{
				CurrentHealth = PlayerAttributeSet->GetHealth();
				MaxHealth = PlayerAttributeSet->GetMaxHealth();

				CurrentMana = PlayerAttributeSet->GetMana();
				MaxMana = PlayerAttributeSet->GetMaxMana();

				CurrentStamina = PlayerAttributeSet->GetStamina();
				MaxStamina = PlayerAttributeSet->GetMaxStamina();

				InitializeProgressBar(HealthBar, EMainHUDProgressBarType::Health
															, CurrentHealth, MaxHealth);
				InitializeProgressBar(ManaBar, EMainHUDProgressBarType::Mana
															, CurrentMana, MaxMana);
				InitializeProgressBar(StaminaBar, EMainHUDProgressBarType::Stamina
															, CurrentStamina, MaxStamina);

				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
					PlayerAttributeSet->GetHealthAttribute()).AddUObject(
					this, &ThisClass::HandleCurrentHealthChanged);
				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
					PlayerAttributeSet->GetMaxHealthAttribute()).AddUObject(
					this, &ThisClass::HandleMaxHealthChanged);

				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
					PlayerAttributeSet->GetManaAttribute()).AddUObject(
					this, &ThisClass::HandleCurrentManaChanged);
				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
					PlayerAttributeSet->GetMaxManaAttribute()).AddUObject(
					this, &ThisClass::HandleMaxManaChanged);

				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
					PlayerAttributeSet->GetStaminaAttribute()).AddUObject(
					this, &ThisClass::HandleCurrentStaminaChanged);
				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
					PlayerAttributeSet->GetMaxStaminaAttribute()).AddUObject(
					this, &ThisClass::HandleMaxStaminaChanged);
			}
		}
	}
}

void UMainHUD::HandleCurrentHealthChanged(const FOnAttributeChangeData& Data)
{
	CurrentHealth = Data.NewValue;
	SetProgressBarPercent(HealthBar, CurrentHealth / MaxHealth);
}

void UMainHUD::HandleMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	MaxHealth = Data.NewValue;
	SetProgressBarPercent(HealthBar, CurrentHealth / MaxHealth);
	SetProgressBarTransform(HealthBar, EMainHUDProgressBarType::Health
													, MaxHealth);
}

void UMainHUD::HandleCurrentManaChanged(const FOnAttributeChangeData& Data)
{
	CurrentMana = Data.NewValue;
	SetProgressBarPercent(ManaBar, CurrentMana / MaxMana);
}

void UMainHUD::HandleMaxManaChanged(const FOnAttributeChangeData& Data)
{
	MaxMana = Data.NewValue;
	SetProgressBarPercent(ManaBar, CurrentMana / MaxMana);
	SetProgressBarTransform(ManaBar, EMainHUDProgressBarType::Mana, MaxMana);
}

void UMainHUD::HandleCurrentStaminaChanged(const FOnAttributeChangeData& Data)
{
	CurrentStamina = Data.NewValue;
	SetProgressBarPercent(StaminaBar, CurrentStamina / MaxStamina);
}

void UMainHUD::HandleMaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	MaxStamina = Data.NewValue;
	SetProgressBarPercent(StaminaBar, CurrentStamina / MaxStamina);
	SetProgressBarTransform(StaminaBar, EMainHUDProgressBarType::Stamina
													, MaxStamina);
}

float UMainHUD::GetProgressBarStartPosX(const float PlusValue
																				, const EMainHUDProgressBarType Type)
const
{
	// Main HUD에 실제로 테스트를 하면서 계산한 로직
	if (Type == EMainHUDProgressBarType::Health)
	{
		// scale이 0.01 증가할 때 마다 3씩 증가하기 때문에
		// scale이 1 증가하면 300이 증가한다는 계산식이 나와 300을 곱함
		return PlusValue * 300;
	}
	if (Type == EMainHUDProgressBarType::Mana)
	{
		return PlusValue * 200;
	}
	if (Type == EMainHUDProgressBarType::Stamina)
	{
		return PlusValue * 250;
	}

	return 1.f;
}

void UMainHUD::SetProgressBarPercent(TObjectPtr<UProgressBar> HUDProgressBar
																		, float Percent) const
{
	if (HUDProgressBar)
	{
		HUDProgressBar->SetPercent(Percent);
	}
}

void UMainHUD::SetProgressBarTransform(TObjectPtr<UProgressBar> HUDProgressBar
																			, const EMainHUDProgressBarType Type
																			, const float MaxValue) const
{
	if (HUDProgressBar)
	{
		const float PlusPercentage = (MaxValue - DefaultMaxPercentValue) *
			BarIncreasePercent;

		FWidgetTransform NewTransform = FWidgetTransform();
		NewTransform.Scale = FVector2d(1 + PlusPercentage, 1);

		NewTransform.Translation = FVector2d(
			GetProgressBarStartPosX(PlusPercentage, Type), 1);
		HUDProgressBar->SetRenderTransform(NewTransform);
	}
}


void UMainHUD::InitializeProgressBar(TObjectPtr<UProgressBar> HUDProgressBar
																		, const EMainHUDProgressBarType Type
																		, const float CurrentValue
																		, const float MaxValue)
{
	if (HUDProgressBar)
	{
		SetProgressBarPercent(HUDProgressBar, CurrentValue / MaxValue);
		SetProgressBarTransform(HUDProgressBar, Type, MaxValue);
	}
}
