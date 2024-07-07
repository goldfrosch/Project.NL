#pragma once

#include "CoreMinimal.h"
#include "CombatManager.generated.h"

class AWeaponBase;

UENUM()
enum EHandEquipStatus
{
	Empty,
	OnlyMain,
	OnlySub,
	Dual,
};

UCLASS()
class PROJECTNL_API UCombatManager : public UObject
{
	
	GENERATED_BODY()
	
public:
	UFUNCTION()
	static void UnSheathCharacterWeapon(const ACharacter* Character, AWeaponBase* Weapon, const bool IsMain);

	// TODO: GetUnSheathingAnimation의 1~3인자는 추후 기본 캐릭터에 대한 base class가 완성되면 parameter 줄이기 마이그레이션을 진행한다.
	UFUNCTION()
	static UAnimMontage* GetUnSheathingAnimation(FDataTableRowHandle CombatDT, AWeaponBase* MainWeapon, AWeaponBase* SubWeapon);

	// TODO: 추후 인벤 관리 or 무기 관리 manager로 마이그레이션 + 유틸로 옮기는 것이 좋아보임
	static EHandEquipStatus GetCharacterEquipStatus(const AWeaponBase* MainWeapon, const AWeaponBase* SubWeapon);
};
