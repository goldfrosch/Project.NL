#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPostProcessComponent;
class UInputAction;
class UPlayerCameraComponent;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class PROJECTNL_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action)
	TObjectPtr<UPlayerCameraComponent> PlayerCameraComponent;

protected:
	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void
	SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveTo(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input
		, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input"
		, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input"
		, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookInputAction;
};
