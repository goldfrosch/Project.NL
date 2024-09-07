#pragma once

#include "CoreMinimal.h"
#include "CombatManager.generated.h"

class AWeaponBase;
class UAbilitySystemComponent;
enum class EPlayerCombatWeaponState : uint8;

UCLASS()
class PROJECTNL_API UCombatManager : public UObject
{
	GENERATED_BODY()

public:
	// TODO: GetUnSheathingAnimation의 1~3인자는 추후 기본 캐릭터에 대한 base class가 완성되면 parameter 줄이기 마이그레이션을 진행한다.
	UFUNCTION()
	static UAnimMontage* GetUnEquipAnimation(const FDataTableRowHandle CombatDT
																					, const EPlayerCombatWeaponState
																					CurrentEquipStatus);

	UFUNCTION()
	static UAnimMontage* GetEquipAnimation(const FDataTableRowHandle CombatDT
																				, const EPlayerCombatWeaponState
																				CurrentEquipStatus);

	UFUNCTION()
	static UAnimMontage* GetDoubleJumpAnimation(const FDataTableRowHandle CombatDT
																							, const EPlayerCombatWeaponState
																							CurrentEquipStatus);

	UFUNCTION()
	static UAnimMontage* GetDamagedAnimation(const FDataTableRowHandle CombatDT
																					, FVector DamagedActorVector
																					, FRotator DamagedActorRotator);

	UFUNCTION()
	static TArray<UAnimMontage*> GetAttackAnimation(
		const FDataTableRowHandle CombatDT
		, const EPlayerCombatWeaponState CurrentEquipStatus);

	UFUNCTION(BlueprintCallable)
	static bool IsCharacterCombat(const UAbilitySystemComponent* Ability);
};
