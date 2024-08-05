#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetsComponent.generated.h"

class UWidgetComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTNL_API UWidgetsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWidgetsComponent();

	void ToggleFixedViewWidget(const bool IsActive);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Entity|Widget"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> FixedViewWidget;

protected:
	virtual void BeginPlay() override;
};
