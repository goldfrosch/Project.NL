// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetsComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "ProjectNL/Character/BaseCharacter.h"


UWidgetsComponent::UWidgetsComponent()
{
	FixedViewWidget = CreateDefaultSubobject<UWidgetComponent>(
		TEXT("Fixed View Widget"));

	if (FixedViewWidget)
	{
		FixedViewWidget->SetWidgetSpace(EWidgetSpace::Screen);
		if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner()))
		{
			FVector FixedViewWidgetPos = OwnerCharacter->GetCapsuleComponent()->
																									GetCenterOfMass();
			FixedViewWidgetPos.Z += OwnerCharacter->GetCapsuleComponent()->
																							GetScaledCapsuleHalfHeight() *
				0.75;

			FixedViewWidget->SetRelativeLocation(FixedViewWidgetPos);

			static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass = TEXT(
				"/Game/Widgets/WB_FixedViewPoint.WB_FixedViewPoint");

			if (WidgetClass.Succeeded())
			{
				FixedViewWidget->SetWidgetClass(WidgetClass.Class);
			}
		}
	}
}

void UWidgetsComponent::BeginPlay()
{
	Super::BeginPlay();
	ToggleFixedViewWidget(false);
}

void UWidgetsComponent::ToggleFixedViewWidget(const bool IsActive)
{
	FixedViewWidget->SetVisibility(IsActive);
}
