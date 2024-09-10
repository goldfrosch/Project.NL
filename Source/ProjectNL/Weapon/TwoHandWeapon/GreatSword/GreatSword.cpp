#include "GreatSword.h"


AGreatSword::AGreatSword()
{
	WeaponType = EUWeaponType::GreatSword;
	EquippedHandType = EUEquippedHandType::TwoHand;
}

void AGreatSword::BeginPlay()
{
	Super::BeginPlay();
}
