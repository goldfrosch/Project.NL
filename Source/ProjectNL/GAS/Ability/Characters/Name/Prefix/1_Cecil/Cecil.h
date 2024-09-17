#pragma once

#include "CoreMinimal.h"
#include "ProjectNL/GAS/Ability/Utility/PassiveAbility.h"
#include "Cecil.generated.h"

UCLASS()
class PROJECTNL_API UCecil : public UPassiveAbility
{
	GENERATED_BODY()

public:
	UCecil();

protected:
	virtual void OnActivateAbility() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> PostProcessMaterial;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> BuffEffect;
};
