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

	// 임시 속성으로 주기적인 업데이트가 필요한 속성은 아니라 OnRep를 할당하지 않음
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Damage)

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

	// TODO: 복제에 도움이 되는 함수지만 정확한 기능은 추후
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
