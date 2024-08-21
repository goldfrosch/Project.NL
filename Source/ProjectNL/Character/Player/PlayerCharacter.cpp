#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Component/PlayerCameraComponent.h"
#include "ProjectNL/GAS/NLAbilitySystemComponent.h"
#include "ProjectNL/Helper/StateHelper.h"
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

// PlayerState 변경 시에 대한 처리
// 변경되는 경우 보통 캐릭터도 같이 변하기에 한번 실행된다고 생각하면 편하다
void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (APlayerStateBase* PS = GetPlayerState<APlayerStateBase>())
	{
		AbilitySystemComponent =
			UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PS);
		if (UNLAbilitySystemComponent* ASC = Cast<UNLAbilitySystemComponent>(
			AbilitySystemComponent))
		{
			ASC->InitializeAbilitySystem(InitializeData, PS, this);
		}
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent =
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPlayerState());

	if (UNLAbilitySystemComponent* ASC = Cast<UNLAbilitySystemComponent>(
		AbilitySystemComponent))
	{
		ASC->InitializeAbilitySystem(InitializeData, this, this);
	}

	SetOwner(NewController);
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

	if (APlayerStateBase* PS = GetPlayerState<APlayerStateBase>())
	{
		if (UNLAbilitySystemComponent* ASC = Cast<UNLAbilitySystemComponent>(
			AbilitySystemComponent))
		{
			ASC->InitializeAbilitySystem(InitializeData, PS, this);
		}
	}

	CombatComponent->UpdateCombatStatus();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
