// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UBasicAttributeSet::OnRepHealth(const FGameplayAttributeData& OldHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Health, OldHealth);
}

void UBasicAttributeSet::OnRepMaxHealth(const FGameplayAttributeData& OldMaxHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, MaxHealth, OldMaxHealth);
}

void UBasicAttributeSet::OnRepMana(const FGameplayAttributeData& OldMana) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Mana, OldMana);
}

void UBasicAttributeSet::OnRepMaxMana(const FGameplayAttributeData& OldMaxMana) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, MaxMana, OldMaxMana);
}

void UBasicAttributeSet::OnRepStamina(const FGameplayAttributeData& OldStamina) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Stamina, OldStamina);
}

void UBasicAttributeSet::OnRepMaxStamina(const FGameplayAttributeData& OldMaxStamina) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, MaxStamina, OldMaxStamina);
}

void UBasicAttributeSet::OnRepLevel(const FGameplayAttributeData& OldLevel) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Level, OldLevel);
}

void UBasicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Level, COND_None, REPNOTIFY_Always);
}

void UBasicAttributeSet::InitBaseAttribute()
{
	InitLevel(1);
	
	InitEndurance(10);
	InitMuscularPower(10);
	InitWisdom(10);
	InitConcentration(10);
	InitSharpness(10);
	InitGuts(10);
	
	InitMaxHealth(200 + GetEndurance() * 20);
	InitHealth(GetMaxHealth());
	InitMaxMana(100);
	InitMana(GetMaxMana());
	InitMaxStamina(100);
	InitStamina(GetStamina());
	
	InitPhysicalDamage(10 + GetMuscularPower() * 5);
	InitMagicalDamage(10 + GetWisdom() * 5);
	InitMovementSpeed(360 + GetEndurance() * 0.06);
	InitDefense(10);
	InitCriticalPercent(10 + GetConcentration() * 0.01);
	InitCriticalPower(10 + GetSharpness() * 0.005);
}
