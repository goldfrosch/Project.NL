#pragma once

class FEnumHelper
{
public:
	template<typename EnumType>
	static FString GetClassEnumKeyAsString(const EnumType EnumeratorValue)
	{
		TArray<FString> EnumKey;
		UEnum::GetValueAsString(EnumeratorValue).ParseIntoArray(EnumKey, TEXT("::"));

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
	Undefined		UMETA(DisplayName = "Undefined"),
	Idle			UMETA(DisplayName = "Idle"),
	DrawWeapon		UMETA(DisplayName = "DrawWeapon"),
	SheathWeapon	UMETA(DisplayName = "SheathWeapon"),
	ComboAttack		UMETA(DisplayNAme = "ComboAttack")
};


UENUM(BlueprintType)
enum class EUEquippedHandType : uint8
{
	Empty		UMETA(DisplayName = "Empty"),
	OneHand		UMETA(DisplayName = "OneHand"),
	TwoHand		UMETA(DisplayName = "TwoHand"),
};

UENUM(BlueprintType)
enum class EUWeaponType : uint8
{
	None		UMETA(DisplayName = "None"),
	Axe			UMETA(DisplayName = "Axe"),
	Sword		UMETA(DisplayName = "Sword"),
	Shield		UMETA(DisplayName = "Shield"),
	Spear		UMETA(DisplayName = "Spear"),
};

UENUM(BlueprintType)
enum class EHandEquipStatus : uint8
{
	Empty		UMETA(DisplayName = "Empty"),
	OnlyMain	UMETA(DisplayName = "OnlyMain"),
	OnlySub		UMETA(DisplayName = "OnlySub"),
	Dual		UMETA(DisplayName = "Dual"),
};

UENUM(BlueprintType)
enum class EPlayerAnimationStatus : uint8
{
	Default,
	Sheathing,
	UnSheathing,
	Attacking
};

UENUM(BlueprintType)
enum class EPlayerCameraStatus: uint8
{
	Third,
	First,
	BowAiming,
};