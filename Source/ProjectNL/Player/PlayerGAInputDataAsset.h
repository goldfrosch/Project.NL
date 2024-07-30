#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "PlayerGAInputDataAsset.generated.h"

class UInputAction;

USTRUCT()
struct FGameplayInputAbilityInfo
{
	GENERATED_USTRUCT_BODY()
 
	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;

	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TObjectPtr<UInputAction> InputAction;
 
	UPROPERTY(VisibleAnywhere, Category = "GameplayInputAbilityInfo")
	int32 InputID;

	bool IsValid() const
	{
		return GameplayAbilityClass && InputAction;
	}
 
	bool operator==(const FGameplayInputAbilityInfo& Other) const
	{
		return GameplayAbilityClass == Other.GameplayAbilityClass && InputAction == Other.InputAction;
	}

	bool operator!=(const FGameplayInputAbilityInfo& Other) const
	{
		return !operator==(Other);
	}

	friend uint32 GetTypeHash(const FGameplayInputAbilityInfo& Item)
	{
		return HashCombine(GetTypeHash(Item.GameplayAbilityClass), GetTypeHash(Item.InputAction));
	}
};

UCLASS()
class PROJECTNL_API UPlayerGAInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPlayerGAInputDataAsset(const FObjectInitializer& ObjectInitializer);
	const TSet<FGameplayInputAbilityInfo>& GetInputAbilities() const;
	
protected:
	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TSet<FGameplayInputAbilityInfo> InputAbilities;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
