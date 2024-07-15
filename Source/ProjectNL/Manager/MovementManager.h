// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MovementManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNL_API UMovementManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	static void Move(APawn* Entity, const FVector2D MoveTo) 
	{
		if (const TObjectPtr<AController> Controller = Entity->Controller)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			/**
			 * Move를 하나로 통일시켜도 정상 동작 하는 이유는 Input Mapping에서 전달하는 X,Y,Z값을
			 * 상하좌우에 따라 X,Y,Z 정렬 순서를 바꾸기 때문에 동일 동작이 가능하다
			 * ex. 상의 경우 Y,X,Z 순서대로 제공함으로써 EAxis::X = Y가 매핑되는 방식이다
			 * ex. 좌의 경우 X,Z,Y 순서대로 매핑되어서 EAxis:X = X가 매핑된다
			 */
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			Entity->AddMovementInput(ForwardDirection, static_cast<float>(MoveTo.Y));
			Entity->AddMovementInput(RightDirection, static_cast<float>(MoveTo.X));
		}
	}
};
