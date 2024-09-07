// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ProjectNL/GAS/NLAbilitySystemInitializationData.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "ProjectNL/Helper/UtilHelper.h"
#include "BaseCharacter.generated.h"

class UDamagedComponent;
class AWeaponBase;
class UCombatComponent;
class UWidgetsComponent;
class UBasicAttributeSet;
enum class EEntityCategory : uint8;

UCLASS()
class PROJECTNL_API ABaseCharacter
	: public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat
		, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget
		, meta = (AllowPrivateAccess = "true"))
	UWidgetsComponent* WidgetsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat
		, meta = (AllowPrivateAccess = "true"))
	UDamagedComponent* DamagedComponent;

	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit) override;

	void InitCharacterWeapon();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent
													, AController* EventInstigator
													, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity|Category"
		, meta = (AllowPrivateAccess = "true"))
	EEntityCategory EntityType = EEntityCategory::Undefined;
	GETTER_SETTER(EEntityCategory, EntityType);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity|Status"
		, meta = (AllowPrivateAccess = "true"))
	bool IsFirstEquip = false;
	GETTER(bool, IsFirstEquip);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySystem"
		, meta = (AllowPrivateAccess = "true"))
	FNLAbilitySystemInitializationData InitializeData;

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
};
