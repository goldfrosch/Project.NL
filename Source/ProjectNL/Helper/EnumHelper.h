﻿#pragma once

class FEnumHelper
{
public:
	template <typename EnumType>
	static FString GetClassEnumKeyAsString(const EnumType EnumeratorValue)
	{
		TArray<FString> EnumKey;
		UEnum::GetValueAsString(EnumeratorValue).
			ParseIntoArray(EnumKey, TEXT("::"));

		if (EnumKey.Num() == 1)
		{
			return EnumKey[0];
		}
		return EnumKey[1];
	}
};

UENUM()
enum class EAnimationType : uint8
{
	Undefined UMETA(DisplayName = "Undefined"), Idle UMETA(DisplayName = "Idle")
	, Jump UMETA(DisplayNAme = "Jump")
	, EquipWeapon UMETA(DisplayName = "EquipWeapon")
	, UnEquipWeapon UMETA(DisplayName = "UnEquipWeapon")
	, ComboAttack UMETA(DisplayNAme = "ComboAttack")};


UENUM(BlueprintType)
enum class EUEquippedHandType : uint8
{
	Empty UMETA(DisplayName = "Empty"), OneHand UMETA(DisplayName = "OneHand")
	, TwoHand UMETA(DisplayName = "TwoHand"),
};

UENUM(BlueprintType)
enum class EUWeaponType : uint8
{
	None UMETA(DisplayName = "None"), Axe UMETA(DisplayName = "Axe")
	, Sword UMETA(DisplayName = "Sword"), Shield UMETA(DisplayName = "Shield")
	, Spear UMETA(DisplayName = "Spear") , Dagger UMETA(DisplayName = "Dagger")
	, Hammer UMETA(DisplayName = "Hammer"), Staff UMETA(DisplayName = "Staff")
	, GreatSword UMETA(DisplayName = "GreatSword")
	, NinjaStar UMETA(DisplayName = "NinjaStar")
	, Gauntlet UMETA(DisplayName = "Gauntlet")
	, Bow UMETA(DisplayName = "Bow"), Katana UMETA(DisplayName = "Katana")};

UENUM(BlueprintType)
enum class EHandEquipStatus : uint8
{
	Empty UMETA(DisplayName = "Empty"), OnlyMain UMETA(DisplayName = "OnlyMain")
	, OnlySub UMETA(DisplayName = "OnlySub"), Dual UMETA(DisplayName = "Dual"),
};

UENUM(BlueprintType)
enum class EPlayerAnimationStatus : uint8
{
	Default, Sheathing, UnSheathing, Attacking
};

// TODO: 최종적으로는 3인칭만 쓸 것으로 보여 Deprecated 처리됨
UENUM(BlueprintType)
enum class EPlayerCameraStatus: uint8
{
	Third, First, BowAiming,
};

UENUM(BlueprintType)
enum class EPlayerCombatWeaponState: uint8
{
	// 일반 공격 무기
	None UMETA(DisplayName = "None")
	, OnlyOneHandWeapon UMETA(DisplayName = "OnlyOneHandWeapon")
	, OneHandWeaponAndShield UMETA(DisplayName = "OneHandWeaponAndShield")
	, DualHandWeapon UMETA(DisplayName = "DualHandWeapon")
	, OnlyOneHandDagger UMETA(DisplayName = "OnlyOneHandDagger")
	, OneHandDaggerAndShield UMETA(DisplayName = "OneHandDaggerAndShield")
	, TwoHandGreatSword UMETA(DisplayName = "TwoHandGreatSword")
	, TwoHandSpear UMETA(DisplayName = "TwoHandSpear")
	, TwoHandBlunt UMETA(DisplayName = "TwoHandBlunt")
	// 특수 공격 무기
	, OnlyDualFist UMETA(DisplayName = "OnlyDualFist")
	, OneHandDaggerAndNinjaStar UMETA(DisplayName = "OneHandDaggerAndNinjaStar")
	, TwoHandBow UMETA(DisplayName = "TwoHandBow")
	, TwoHandKatana UMETA(DisplayName = "TwoHandKatana")
	, TwoHandMagicStaff UMETA(DisplayName = "TwoHandMagicStaff")};

UENUM(BlueprintType)
enum class EEntityCategory: uint8
{
	Undefined UMETA(DisplayName = "Undefined")
	, Player UMETA(DisplayName = "Player"), Neutral UMETA(DisplayName = "Neutral")
	, Enemy UMETA(DisplayName = "Enemy"),
};

UENUM(BlueprintType)
enum class EInputIDType: uint8
{
	None UMETA(DisplayName = "None"), Jump UMETA(DisplayName = "Jump")
	, Attack UMETA(DisplayName = "Attack"), Sprint UMETA(DisplayName = "Sprint")
	, ToggleCombatMode UMETA(DisplayName = "ToggleCombatMode")
	, FixedCamera UMETA(DisplayName = "FixedCamera")
	, Skill1 UMETA(DisplayName = "Skill1"), Skill2 UMETA(DisplayName = "Skill2")
	, Skill3 UMETA(DisplayName = "Skill3"), Skill4 UMETA(DisplayName = "Skill4")};

UENUM(BlueprintType)
enum class EDamagedHeight: uint8
{
	Low UMETA(DisplayName = "Low"), Middle UMETA(DisplayName = "Middle"), High
	UMETA(DisplayName = "High")};

UENUM(BlueprintType)
enum class EDamagedDirection: uint8
{
	Front UMETA(DisplayName = "Front"), Back UMETA(DisplayName = "Back")
	, Left UMETA(DisplayName = "Left"), Right UMETA(DisplayName = "Right")};
