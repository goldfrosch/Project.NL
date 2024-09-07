// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectNL/Helper/UtilHelper.h"
#include "DamagedComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTNL_API UDamagedComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamagedComponent();

	void HandleDamaged(AActor* DamageCauser);

	GETTER_SETTER(bool, IsDamaged)

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle DamagedAnimData;

	FTimerHandle HitTimerHandle;

	bool IsDamaged = false;

	void HandleHitEnd();
};
