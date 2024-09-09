#include "OneHandDagger.h"


AOneHandDagger::AOneHandDagger()
{
	WeaponType = EUWeaponType::Dagger;
	EquippedHandType = EUEquippedHandType::OneHand;
}

void AOneHandDagger::BeginPlay()
{
	Super::BeginPlay();
}
