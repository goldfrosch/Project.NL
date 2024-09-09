#include "OneHandSword.h"


AOneHandSword::AOneHandSword()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponType = EUWeaponType::Sword;
	EquippedHandType = EUEquippedHandType::OneHand;
}

void AOneHandSword::BeginPlay()
{
	Super::BeginPlay();
}

void AOneHandSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
