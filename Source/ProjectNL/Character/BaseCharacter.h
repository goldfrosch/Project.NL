// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "ProjectNL/Helper/UtilHelper.h"
#include "BaseCharacter.generated.h"

class UWidgetsComponent;
enum class EEntityCategory : uint8;
class AWeaponBase;
class UCombatComponent;
class UBasicAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class PROJECTNL_API ABaseCharacter
	: public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS"
		, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat
		, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget
		, meta = (AllowPrivateAccess = "true"))
	UWidgetsComponent* WidgetsComponent;

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

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes"
		, meta = (AllowPrivateAccess = "true"))
	const UBasicAttributeSet* AttributeSet;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity|Category"
		, meta = (AllowPrivateAccess = "true"))
	EEntityCategory EntityType = EEntityCategory::Undefined;
	GETTER_SETTER(EEntityCategory, EntityType);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity|Status"
		, meta = (AllowPrivateAccess = "true"))
	bool IsFirstEquip = false;
	GETTER(bool, IsFirstEquip);
};
