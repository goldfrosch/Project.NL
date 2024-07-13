// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class AWeaponBase;
class UBasicAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class PROJECTNL_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter(const class FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;
	
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}
protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
    AWeaponBase* MainWeapon;
  
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
    AWeaponBase* SubWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes", meta = (AllowPrivateAccess = "true"))
	const UBasicAttributeSet* AttributeSet;
	
};
