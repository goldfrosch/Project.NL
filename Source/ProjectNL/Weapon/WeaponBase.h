#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "GameFramework/Actor.h"
#include "ProjectNL/Helper/UtilHelper.h"

#include "WeaponBase.generated.h"

UCLASS()
class PROJECTNL_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetWeaponMesh() const;

	UFUNCTION()
	void SetWeaponDamageable() const;

	UFUNCTION()
	void UnsetWeaponDamageable() const;

	UFUNCTION()
	void EquipCharacterWeapon(ACharacter* Character, const bool IsMain);

	UFUNCTION()
	void UnEquipCharacterWeapon(const bool IsMain);
	void UnEquipCharacterWeapon(ACharacter* Character, const bool IsMain);

	UFUNCTION()
	void SwapTwoHandWeapon();

	GETTER(EUWeaponType, WeaponType)
	GETTER(EWeaponAttachPosition, AttachPosition)

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponSkeleton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* WeaponCollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	EUEquippedHandType EquippedHandType;
	GETTER(EUEquippedHandType, EquippedHandType)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	EUWeaponType WeaponType;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent
											, AActor* OtherActor, UPrimitiveComponent* OtherComp
											, int32 OtherBodyIndex, bool bFromSweep
											, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Assets
		, meta = (AllowPrivateAccess = "true"))
	EWeaponAttachPosition AttachPosition = EWeaponAttachPosition::Back;
};
