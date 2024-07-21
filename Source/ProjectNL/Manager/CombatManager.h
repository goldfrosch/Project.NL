#pragma once

#include "CoreMinimal.h"
#include "CombatManager.generated.h"

class AWeaponBase;

UCLASS()
class PROJECTNL_API UCombatManager : public UObject
{
	GENERATED_BODY()
public:
	// TODO: GetUnSheathingAnimation의 1~3인자는 추후 기본 캐릭터에 대한 base class가 완성되면 parameter 줄이기 마이그레이션을 진행한다.
	UFUNCTION()
	static UAnimMontage* GetUnSheathingAnimation(FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon);
	
	UFUNCTION()
	static UAnimMontage* GetSheathingAnimation(FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon);

	UFUNCTION()
	static TArray<UAnimMontage*> GetAttackAnimation(FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon);
};
