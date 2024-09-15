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
				if (HealthBar)
				{
					HealthBar->SetPercent(CurrentHealth / MaxHealth);
				}

				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
					PlayerAttributeSet->GetHealthAttribute()).AddUObject(
					this, &ThisClass::HandleCurrentHealthChanged);
			}
		}
	}
}

void UMainHUD::HandleCurrentHealthChanged(const FOnAttributeChangeData& Data)
{
	CurrentHealth = Data.NewValue;
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}
