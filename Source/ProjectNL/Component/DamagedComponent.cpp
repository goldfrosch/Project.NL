#include "DamagedComponent.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "ProjectNL/Manager/CombatManager.h"


UDamagedComponent::UDamagedComponent()
{
}


void UDamagedComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDamagedComponent::HandleDamaged(AActor* DamageCauser)
{
	if (GetIsDamaged())
	{
		return;
	}

	AActor* Owner = GetOwner();

	SetIsDamaged(true);

	const FVector StartVector = Owner->GetActorLocation();
	const FVector TargetVector = DamageCauser->GetActorLocation();
	const FVector HitDetection = TargetVector - StartVector;

	const FRotator OwnerRotator = UKismetMathLibrary::FindLookAtRotation(
		StartVector, TargetVector);

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(Owner))
	{
		Character->StopAnimMontage();
		Character->PlayAnimMontage(
			UCombatManager::GetDamagedAnimation(DamagedAnimData, HitDetection
																					, OwnerRotator));
	}

	Owner->GetWorldTimerManager().SetTimer(HitTimerHandle, this
																				, &ThisClass::HandleHitEnd, 0.25
																				, false);
}

void UDamagedComponent::HandleHitEnd()
{
	SetIsDamaged(false);
}
