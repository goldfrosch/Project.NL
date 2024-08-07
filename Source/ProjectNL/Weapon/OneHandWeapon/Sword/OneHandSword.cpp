﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "OneHandSword.h"


// Sets default values
AOneHandSword::AOneHandSword()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponType = EUWeaponType::Sword;
	EquippedHandType = EUEquippedHandType::OneHand;
}

// Called when the game starts or when spawned
void AOneHandSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOneHandSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

