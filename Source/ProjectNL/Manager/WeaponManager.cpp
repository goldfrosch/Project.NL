#include "WeaponManager.h"

#include "GameFramework/Character.h"
#include "ProjectNL/Weapon/WeaponBase.h"

void UWeaponManager::EquipCharacterWeapon(const ACharacter* Character
																					, AWeaponBase* Weapon
																					, const bool IsMain)
{
	if (!IsValid(Character) || !IsValid(Weapon))
	{
		return;
	}

	Weapon->AttachToComponent(Character->GetMesh()
														, FAttachmentTransformRules::SnapToTargetIncludingScale
														, IsMain ? "weapon_r" : "weapon_l");
}

void UWeaponManager::UnEquipCharacterWeapon(const ACharacter* Character
																						, AWeaponBase* Weapon
																						, const bool IsMain)
{
	if (!IsValid(Character) || !IsValid(Weapon))
	{
		return;
	}

	Weapon->AttachToComponent(Character->GetMesh()
														, FAttachmentTransformRules::SnapToTargetIncludingScale
														, IsMain ? "weapon_back_r" : "weapon_back_l");
	Weapon->InitEquipWeapon();
}

void UWeaponManager::StartEquipCharacterWeapon(AWeaponBase* Weapon)
{
	if (Weapon)
	{
		const FRotator CurrentRotator = Weapon->GetWeaponMesh()->
																						GetRelativeRotation();
		const FRotator NewRotator = FRotator(CurrentRotator.Pitch
																				, CurrentRotator.Yaw
																				, 180 - CurrentRotator.Roll);

		Weapon->GetWeaponMesh()->SetRelativeRotation(NewRotator);
	}
}

EHandEquipStatus UWeaponManager::GetCharacterEquipStatus(
	const AWeaponBase* MainWeapon, const AWeaponBase* SubWeapon)
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
