// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

class UBasicAttributeSet;
class UAbilitySystemComponent;
struct FOnAttributeChangeData;

UCLASS()
class PROJECTNL_API ADefaultPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ADefaultPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UBasicAttributeSet* AttributeSet;

	FDelegateHandle HealthChangedDelegateHandle;
	
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
};
