#pragma once
#include "ProjectNL/Weapon/WeaponBase.h"
#include "ProjectNL/Manager/WeaponManager.h"
#include "ProjectNL/Helper/EnumHelper.h"

enum class EUWeaponType : uint8;
class UWeaponManager;

class FAnimHelper
{
public:
	static FString GetCombatAttackAnimation
	(const FDataTableRowHandle CombatData, const AWeaponBase* MainWeapon, const AWeaponBase* SubWeapon)
	{
		const EHandEquipStatus CurrentEquipStatus =
			UWeaponManager::GetCharacterEquipStatus(MainWeapon, SubWeapon);
		
		const FString EquipStatus = FEnumHelper::GetClassEnumKeyAsString(CurrentEquipStatus);

		
		const EUEquippedHandType MainWeaponHandType = MainWeapon ? MainWeapon->EquippedHandType : EUEquippedHandType::Empty;
		
		const FString MainHandStatus =  FEnumHelper::GetClassEnumKeyAsString(MainWeaponHandType);
		
		const EUWeaponType MainWeaponType = MainWeapon ? MainWeapon->WeaponType : EUWeaponType::None;
		
		const FString MainHandType =  FEnumHelper::GetClassEnumKeyAsString(MainWeaponType);
		
		
		const EUWeaponType SubWeaponType = SubWeapon ? SubWeapon->WeaponType : EUWeaponType::None;
		
		const FString SubHandType =  FEnumHelper::GetClassEnumKeyAsString(SubWeaponType);
		
		return EquipStatus + MainHandStatus + MainHandType + SubHandType + "AttackAnim";
	}
};
