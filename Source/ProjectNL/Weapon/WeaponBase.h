#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "ProjectNL/Helper/EnumHelper.h"
#include "GameFramework/Actor.h"
#include "ProjectNL/Helper/UtilHelper.h"

#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FWeaponAttackNotified
																						, UPrimitiveComponent*
																						, OverlappedComponent, AActor*
																						, OtherActor, UPrimitiveComponent*
																						, OtherComp, int32, OtherBodyIndex
																						, bool, bFromSweep
																						, const FHitResult&, SweepResult);

UCLASS()
class PROJECTNL_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetWeaponMesh() const;

	FWeaponAttackNotified OnNotifiedAttack;

	UFUNCTION()
	void SetWeaponDamageable() const;

	UFUNCTION()
	void UnsetWeaponDamageable() const;

	UFUNCTION()
	void GiveDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
									, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
									, bool bFromSweep, const FHitResult& SweepResult);

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
	GETTER(EUWeaponType, WeaponType)
};
