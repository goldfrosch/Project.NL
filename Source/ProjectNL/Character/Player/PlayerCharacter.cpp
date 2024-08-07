﻿#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Component/PlayerCameraComponent.h"
#include "ProjectNL/GAS/Attribute/BasicAttributeSet.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/MovementManager.h"
#include "ProjectNL/Player/DefaultPlayerState.h"
#include "ProjectNL/Player/PlayerGAInputDataAsset.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 450.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 50.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	PlayerCameraComponent = CreateDefaultSubobject<UPlayerCameraComponent>(
		TEXT("Camera Component"));
	PlayerCameraComponent->CameraSpring->SetupAttachment(RootComponent);
	PlayerCameraComponent->ThirdFollowCamera->SetupAttachment(
		PlayerCameraComponent->CameraSpring, USpringArmComponent::SocketName);

	SetEntityType(EEntityCategory::Player);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();
	CombatComponent->UpdateCombatStatus();

	// TODO: 추후 패시브 Ability로 추가
	FGameplayTagContainer InitContainer;
	InitContainer.AddTag(NlGameplayTags::State_Player_Idle);
	InitContainer.AddTag(NlGameplayTags::Ability_Util_DoubleJump);

	GetAbilitySystemComponent()->AddLooseGameplayTags(InitContainer);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// TODO: BeginPlay보다 먼저 호출되고 2번 호출되는 함수
void APlayerCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(
		GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<
		UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered
																			, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered
																			, this, &APlayerCharacter::Look);

		if (PlayerGAInputDataAsset)
		{
			const TSet<FGameplayInputAbilityInfo>& InputAbilities =
				PlayerGAInputDataAsset->GetInputAbilities();
			for (const auto& It : InputAbilities)
			{
				if (It.IsValid())
				{
					const UInputAction* InputAction = It.InputAction;
					const int32 InputID = It.InputID;

					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started
																						, this
																						, &
																						APlayerCharacter::OnAbilityInputPressed
																						, InputID);
					EnhancedInputComponent->BindAction(InputAction
																						, ETriggerEvent::Completed, this
																						, &
																						APlayerCharacter::OnAbilityInputReleased
																						, InputID);
				}
			}
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (FStateHelper::IsPlayerIdle(GetAbilitySystemComponent()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		UMovementManager::Move(this, MovementVector);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const float NewPitch = LookAxisVector.Y *
			UGameplayStatics::GetWorldDeltaSeconds(this) * 60.f;
		const float NewYaw = LookAxisVector.X *
			UGameplayStatics::GetWorldDeltaSeconds(this) * 60.f;

		AddControllerYawInput(NewYaw);
		AddControllerPitchInput(NewPitch);
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (ADefaultPlayerState* PS = GetPlayerState<ADefaultPlayerState>())
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(
			PS->GetAbilitySystemComponent());
		// BaseCharacter에서도 init 과정은 있었지만 플레이어의 경우는 playerState가 적용될 때 owner에 playerState를 넣어준다.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (ADefaultPlayerState* PS = GetPlayerState<ADefaultPlayerState>())
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(
			PS->GetAbilitySystemComponent());
		// BaseCharacter에서도 init 과정은 있었지만 플레이어의 경우는 playerState가 적용될 때 owner에 playerState를 넣어준다.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void APlayerCharacter::InitAbilitySystem()
{
	GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetMovementSpeed();
	if (PlayerGAInputDataAsset)
	{
		for (const FGameplayInputAbilityInfo& It : PlayerGAInputDataAsset->
				GetInputAbilities())
		{
			if (It.IsValid())
			{
				constexpr int32 AbilityLevel = 1;
				const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(
					It.GameplayAbilityClass, AbilityLevel, It.InputID);
				AbilitySystemComponent->GiveAbility(AbilitySpec);
			}
		}
		if (const APlayerController* PlayerController = Cast<APlayerController>(
			Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
					PlayerController->GetLocalPlayer()))
			{
				constexpr int32 Priority = 0;
				Subsystem->AddMappingContext(DefaultMappingContext, Priority);
			}
		}
	}
}

void APlayerCharacter::OnAbilityInputPressed(const int32 InputID)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(InputID);
	}
}

void APlayerCharacter::OnAbilityInputReleased(const int32 InputID)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputReleased(InputID);
	}
}
