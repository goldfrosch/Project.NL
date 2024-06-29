// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponOneHandSword.h"


// Sets default values
AWeaponOneHandSword::AWeaponOneHandSword()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponType = EUWeaponType::ET_OneHandSword;
}

// Called when the game starts or when spawned
void AWeaponOneHandSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponOneHandSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

