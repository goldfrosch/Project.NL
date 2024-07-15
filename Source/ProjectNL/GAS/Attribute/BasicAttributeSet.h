// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
// ATTRIBUTE_ACCESSORS 선언시 GAMEPLAYATTRIBUTE_VALUE_SETTER에서 ASC를 사용함
#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECTNL_API UBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	// TODO: 복제에 도움이 되는 함수지만 정확한 기능은 추후
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitBaseAttribute();

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRepHealth)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRepMaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRepMana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Mana)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRepMaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MaxMana)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRepStamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Stamina)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRepMaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MaxStamina)

	// 실제 반영 스텟 Meta Attribute
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, PhysicalDamage)

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MagicalDamage;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MagicalDamage)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Defense)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MovementSpeed)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData CriticalPercent;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, CriticalPercent)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData CriticalPower;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, CriticalPower)

	// 수치 조절 스텟 Meta Attribute
	// 지구력
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Endurance)

	// 근력
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MuscularPower;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MuscularPower)

	// 지혜
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Wisdom)

	// 집중
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Concentration;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Concentration)

	// 예리
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Sharpness;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Sharpness)

	// 근성
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Guts;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Guts)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRepLevel)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Level)

	UFUNCTION()
	virtual void OnRepHealth(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRepMaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRepMana(const FGameplayAttributeData& OldMana);
	UFUNCTION()
	virtual void OnRepMaxMana(const FGameplayAttributeData& OldMaxMana);
	UFUNCTION()
	virtual void OnRepStamina(const FGameplayAttributeData& OldStamina);
	UFUNCTION()
	virtual void OnRepMaxStamina(const FGameplayAttributeData& OldMaxStamina);
	UFUNCTION()
	virtual void OnRepLevel(const FGameplayAttributeData& OldLevel);
};
