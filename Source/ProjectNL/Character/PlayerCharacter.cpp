// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectNL/Animation/Characters/UnSheathing/GrabWeaponNotify.h"
#include "ProjectNL/Animation/Characters/UnSheathing/UnSheathingEndNotify.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Manager/CombatManager.h"
#include "ProjectNL/Manager/MovementManager.h"
#include "ProjectNL/Weapon/WeaponBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 550.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraSpring->SetupAttachment(RootComponent);
	CameraSpring->TargetArmLength = 400.0f;
	CameraSpring->bUsePawnControlRotation = true;
	
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment(GetMesh(), "head");
	FirstCamera->bUsePawnControlRotation = true;
	
	ThirdFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdFollowCamera"));
	ThirdFollowCamera->SetupAttachment(CameraSpring, USpringArmComponent::SocketName);
	ThirdFollowCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetThirdPersonView();

	MainWeapon = GetWorld()->SpawnActor<AWeaponBase>(TestWeapon);

	if (const TObjectPtr<UAnimMontage> UnSheathingAnim = UCombatManager::GetUnSheathingAnimation(CombatAnimData, MainWeapon, SubWeapon)) {
		if (const TObjectPtr<UGrabWeaponNotify> GrabWeaponNotify =
    		UAnimNotifyManager::FindNotifyByClass<UGrabWeaponNotify>(UnSheathingAnim))
    	{
    		GrabWeaponNotify->OnNotified.AddDynamic(this, &APlayerCharacter::UnSheathPlayer);
    	}
		if (const TObjectPtr<UUnSheathingEndNotify> UnSheathingEndNotify =
			UAnimNotifyManager::FindNotifyByClass<UUnSheathingEndNotify>(UnSheathingAnim))
		{
			UnSheathingEndNotify->OnNotified.AddDynamic(this, &APlayerCharacter::SheathingEndPlayer);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// TODO: BeginPlay보다 먼저 호출되고 2번 호출되는 함수
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Run);
		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(ScrollCloseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ScrollClose);
		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleCombatMode);
	}
}

void APlayerCharacter::ScrollClose(const FInputActionValue& Value)
{
	const float ScrollAxis = Value.Get<float>();

	if (GetIsFirstPersonView())
	{
		if (ScrollAxis == 1)
		{
			CountForChangeThirdPerson = 0;
			CameraSpring->TargetArmLength = 0;
			SetFirstPersonView();
		} else if (ScrollAxis == -1)
		{
			CountForChangeThirdPerson++;
			if (CountForChangeThirdPerson == MaxCountForChangeThirdPerson)
			{
				CameraSpring->TargetArmLength = 160;
				SetThirdPersonView();
			}
		}
	} else
	{
		CameraSpring->TargetArmLength -= ScrollAxis * PercentCameraMovement;
	}
}

void APlayerCharacter::Run(const FInputActionValue& Value)
{
	const bool IsRunning = Value.Get<bool>();
	GetCharacterMovement()->MaxWalkSpeed = IsRunning ? 450.f : 250.f;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (AnimStatus == Default)
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
		const float NewPitch = LookAxisVector.Y * UGameplayStatics::GetWorldDeltaSeconds(this) * 100.f;
		const float NewYaw = LookAxisVector.X * UGameplayStatics::GetWorldDeltaSeconds(this) * 100.f;
            
		AddControllerYawInput(NewYaw);
		AddControllerPitchInput(NewPitch);
	}
}

void APlayerCharacter::SetFirstPersonView()
{
	FirstCamera->SetActive(true);
	ThirdFollowCamera->SetActive(false);
	bUseControllerRotationYaw = true;
}

void APlayerCharacter::SetThirdPersonView()
{
	FirstCamera->SetActive(false);
	ThirdFollowCamera->SetActive(true);
	bUseControllerRotationYaw = false;
}

bool APlayerCharacter::GetIsFirstPersonView() const
{
	return CameraSpring->TargetArmLength <= static_cast<float>(MaxCameraScroll);
}

void APlayerCharacter::ToggleCombatMode()
{
	if (IsCombatMode)
	{
		AnimStatus = Sheathing;
		IsCombatMode = false;
	} else
	{
		AnimStatus = UnSheathing;
		IsCombatMode = true;
		if (const TObjectPtr<UAnimMontage> UnSheathingAnim = UCombatManager::GetUnSheathingAnimation(CombatAnimData, MainWeapon, SubWeapon))
		{
			PlayAnimMontage(UnSheathingAnim);
		}
	}
}

void APlayerCharacter::UnSheathPlayer()
{
	UCombatManager::UnSheathCharacterWeapon(this, MainWeapon, true);
	UCombatManager::UnSheathCharacterWeapon(this, SubWeapon, false);
}

void APlayerCharacter::SheathingEndPlayer()
{
	AnimStatus = Default;
}
