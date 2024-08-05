#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "ProjectNL/Helper/UtilHelper.h"
#include "CombatComponent.generated.h"


enum class EPlayerCombatWeaponState : uint8;
class AWeaponBase;

UCLASS()
class PROJECTNL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

	UFUNCTION()
	void UpdateCombatStatus();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State
		, meta = (AllowPrivateAccess = "true"))
	EPlayerCombatWeaponState PlayerCombatWeaponState =
		EPlayerCombatWeaponState::None;
	GETTER_SETTER(EPlayerCombatWeaponState, PlayerCombatWeaponState)

	UPROPERTY(EditAnywhere, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle CombatAnimData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon
		, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> MainWeaponTemplate;
	GETTER(TSubclassOf<AWeaponBase>, MainWeaponTemplate)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon
		, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> SubWeaponTemplate;
	GETTER(TSubclassOf<AWeaponBase>, SubWeaponTemplate)

	UPROPERTY(BlueprintReadOnly, Category = Weapon
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponBase> MainWeapon;
	GETTER_SETTER(TObjectPtr<AWeaponBase>, MainWeapon)

	UPROPERTY(BlueprintReadOnly, Category = Weapon
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponBase> SubWeapon;
	GETTER_SETTER(TObjectPtr<AWeaponBase>, SubWeapon)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> EquipAnim;
	GETTER(TObjectPtr<UAnimMontage>, EquipAnim)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> UnEquipAnim;
	GETTER(TObjectPtr<UAnimMontage>, UnEquipAnim)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DoubleJumpAnim;
	GETTER(TObjectPtr<UAnimMontage>, DoubleJumpAnim)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation
		, meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UAnimMontage>> ComboAttackAnim;
	GETTER(TArray<TObjectPtr<UAnimMontage>>, ComboAttackAnim)
};
