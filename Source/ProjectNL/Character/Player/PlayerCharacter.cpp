#include "PlayerCharacter.h"

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

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (ADefaultPlayerState* PS = GetPlayerState<ADefaultPlayerState>())
	{
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		// BaseCharacter에서도 init 과정은 있었지만 플레이어의 경우는 playerState가 적용될 때 owner에 playerState를 넣어준다.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (ADefaultPlayerState* PS = GetPlayerState<ADefaultPlayerState>())
	{
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		// BaseCharacter에서도 init 과정은 있었지만 플레이어의 경우는 playerState가 적용될 때 owner에 playerState를 넣어준다.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();
	CombatComponent->UpdateCombatStatus();

	InitTag();
}

void APlayerCharacter::InitTag()
{
	GetAbilitySystemComponent()->SetLooseGameplayTagCount(
		NlGameplayTags::State_Player_Idle, 1);
	GetAbilitySystemComponent()->SetLooseGameplayTagCount(
		NlGameplayTags::Ability_Util_DoubleJump, 1);
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
	for (const auto CurrentTag : GetAbilitySystemComponent()->
			GetOwnedGameplayTags())
	{
		UE_LOG(LogTemp, Display, TEXT("TEST1: %s")
					, *CurrentTag.GetTagName().ToString());
	}

	if (APlayerCharacter* SecondPlayer = Cast<APlayerCharacter>(
		UGameplayStatics::GetPlayerPawn(this->GetWorld(), 1)))
	{
		for (const auto CurrentTag : SecondPlayer->GetAbilitySystemComponent()->
																							GetOwnedGameplayTags())
		{
			UE_LOG(LogTemp, Display, TEXT("TEST2: %s")
						, *CurrentTag.GetTagName().ToString());
		}
	}

	if (FStateHelper::IsPlayerIdle(GetAbilitySystemComponent()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		UMovementManager::Move(this, MovementVector);
	}
	Server_Move_Implementation(Value);
}

void APlayerCharacter::Server_Move_Implementation(
	const FInputActionValue& Value)
{
	if (FStateHelper::IsPlayerIdle(GetAbilitySystemComponent()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		UMovementManager::Move(this, MovementVector);
	}
}

bool APlayerCharacter::Server_Move_Validate(const FInputActionValue& Value)
{
	// 제한 조건 만들어두기
	return true;
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

void APlayerCharacter::InitAbilitySystem()
{
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
