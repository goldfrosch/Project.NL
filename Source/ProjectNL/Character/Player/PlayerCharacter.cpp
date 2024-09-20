#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Component/PlayerCameraComponent.h"
#include "ProjectNL/GAS/Attribute/PlayerAttributeSet.h"
#include "ProjectNL/Helper/StateHelper.h"
#include "ProjectNL/Manager/MovementManager.h"
#include "ProjectNL/Player/PlayerControllerBase.h"
#include "ProjectNL/Player/PlayerStateBase.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 50.f;
	GetCharacterMovement()->MaxWalkSpeed = 280;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	PlayerCameraComponent = CreateDefaultSubobject<UPlayerCameraComponent>(
		TEXT("Camera Component"));
	PlayerCameraComponent->CameraSpring->SetupAttachment(RootComponent);
	PlayerCameraComponent->ThirdFollowCamera->SetupAttachment(
		PlayerCameraComponent->CameraSpring, USpringArmComponent::SocketName);

	SetEntityType(EEntityCategory::Player);
}

// PlayerState 변경 시에 대한 처리
// 변경되는 경우 보통 캐릭터도 같이 변하기에 한번 실행된다고 생각하면 편하다
void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (APlayerStateBase* PS = GetPlayerState<APlayerStateBase>())
	{
		AbilitySystemComponent = Cast<UNLAbilitySystemComponent>(
			PS->GetAbilitySystemComponent());

		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		PlayerAttributeSet = PS->AttributeSet;
		PlayerAttributeSet->InitBaseAttribute();

		if (APlayerControllerBase* PC = Cast<
			APlayerControllerBase>(GetController()))
		{
			PC->CreateMainHUD();
		}
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerStateBase* PS = GetPlayerState<APlayerStateBase>())
	{
		AbilitySystemComponent = Cast<UNLAbilitySystemComponent>(
			PS->GetAbilitySystemComponent());

		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		PlayerAttributeSet = PS->AttributeSet;
		PlayerAttributeSet->InitBaseAttribute();

		AbilitySystemComponent->InitializeAbilitySystem(InitializeData);

		if (APlayerControllerBase* PC = Cast<
			APlayerControllerBase>(GetController()))
		{
			PC->CreateMainHUD();
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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

	CombatComponent->UpdateCombatStatus();
}

void APlayerCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<
		UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered
																			, this, &ThisClass::MoveTo);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered
																			, this, &ThisClass::Look);
	}
}

void APlayerCharacter::MoveTo(const FInputActionValue& Value)
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
