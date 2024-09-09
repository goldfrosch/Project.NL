#include "WeaponManager.h"

#include "ProjectNL/Weapon/WeaponBase.h"

EHandEquipStatus UWeaponManager::GetCharacterEquipStatus(
	AWeaponBase* MainWeapon, AWeaponBase* SubWeapon)
{
	if (!IsValid(MainWeapon) && !IsValid(SubWeapon))
	{
		return EHandEquipStatus::Empty;
	}
	if (!IsValid(MainWeapon))
	{
		return EHandEquipStatus::OnlySub;
	}
	if (!IsValid(SubWeapon))
	{
		return EHandEquipStatus::OnlyMain;
	}

	if (MainWeapon->WeaponType != EUWeaponType::None)
	{
		if (SubWeapon->GetWeaponType() != EUWeaponType::None && SubWeapon->
			GetWeaponType() != EUWeaponType::Shield)
		{
			return EHandEquipStatus::Dual;
		}
		return EHandEquipStatus::OnlyMain;
	}
	if (SubWeapon->GetWeaponType() != EUWeaponType::None && SubWeapon->
		GetWeaponType() != EUWeaponType::Shield)
	{
		return EHandEquipStatus::OnlySub;
	}
	return EHandEquipStatus::Empty;
}
