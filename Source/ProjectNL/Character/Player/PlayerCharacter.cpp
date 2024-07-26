#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectNL/Animation/Characters/Attack/ComboAttackStartNotify.h"
#include "ProjectNL/Animation/Characters/Sheathing/GrabWeaponNotify.h"
#include "ProjectNL/Animation/Characters/Sheathing/PutWeaponNotify.h"
#include "ProjectNL/Animation/Characters/Sheathing/UnSheathingEndNotify.h"
#include "ProjectNL/Component/CombatComponent.h"
#include "ProjectNL/Component/PlayerCameraComponent.h"
#include "ProjectNL/Manager/AnimNotifyManager.h"
#include "ProjectNL/Manager/MovementManager.h"
#include "ProjectNL/Manager/WeaponManager.h"
#include "ProjectNL/Player/DefaultPlayerState.h"
#include "ProjectNL/Weapon/WeaponBase.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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
	
	PlayerCameraComponent = CreateDefaultSubobject<UPlayerCameraComponent>(TEXT("Camera Component"));
	PlayerCameraComponent->CameraSpring->SetupAttachment(RootComponent);
	PlayerCameraComponent->FirstCamera->SetupAttachment(GetMesh(), "head");
	PlayerCameraComponent->ThirdFollowCamera->SetupAttachment(
		PlayerCameraComponent->CameraSpring, USpringArmComponent::SocketName);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCameraComponent->SetThirdPersonView();
	PlayerCameraComponent->OnPlayerCameraModeChanged.AddDynamic(this, &APlayerCharacter::OnToggleCamera);

	CombatComponent->SetMainWeapon(GetWorld()->SpawnActor<AWeaponBase>(TestWeapon));
	CombatComponent->SetSubWeapon(GetWorld()->SpawnActor<AWeaponBase>(TestWeapon));

	CombatComponent->OnNotifiedComboAttackStart.AddDynamic(this, &APlayerCharacter::OnAttackStart);
	CombatComponent->OnNotifiedComboAttackEnd.AddDynamic(this, &APlayerCharacter::OnAttackEnd);
	
	SheathPlayer();
	UpdateWeaponData();
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
		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleCombatMode);
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Started,
			PlayerCameraComponent, &UPlayerCameraComponent::ToggleCamera);

		EnhancedInputComponent->BindAction(MainWeaponAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
	}
}

void APlayerCharacter::Run(const FInputActionValue& Value)
{
	const bool IsRunning = Value.Get<bool>();
	GetCharacterMovement()->MaxWalkSpeed = IsRunning ? 450.f : 250.f;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (AnimStatus == EPlayerAnimationStatus::Default)
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
		const float NewPitch = LookAxisVector.Y * UGameplayStatics::GetWorldDeltaSeconds(this) * 60.f;
		const float NewYaw = LookAxisVector.X * UGameplayStatics::GetWorldDeltaSeconds(this) * 60.f;
            
		AddControllerYawInput(NewYaw);
		AddControllerPitchInput(NewPitch);
	}
}

void APlayerCharacter::ToggleCombatMode()
{
	if (AnimStatus == EPlayerAnimationStatus::Default)
	{
		if (IsCombatMode)
		{
			AnimStatus = EPlayerAnimationStatus::Sheathing;
			IsCombatMode = false;
			PlayAnimMontage(CombatComponent->GetSheathAnimMontage());
			return;
		}
		AnimStatus = EPlayerAnimationStatus::UnSheathing;
		IsCombatMode = true;
		PlayAnimMontage(CombatComponent->GetUnSheathAnimMontage());
	}
}

void APlayerCharacter::UpdateWeaponData()
{
	CombatComponent->UpdateWeaponData();
	CombatComponent->OnNotifiedComboAttackInit
	.AddDynamic(this, &APlayerCharacter::InitAttack);

	if (const TObjectPtr<UPutWeaponNotify> PutWeaponNotify =
			UAnimNotifyManager::FindNotifyByClass<UPutWeaponNotify>(CombatComponent->GetSheathAnimMontage()))
	{
		PutWeaponNotify->OnNotified.AddDynamic(this, &APlayerCharacter::SheathPlayer);
	}
	if (const TObjectPtr<UUnSheathingEndNotify> UnSheathingEndNotify =
		UAnimNotifyManager::FindNotifyByClass<UUnSheathingEndNotify>(CombatComponent->GetSheathAnimMontage()))
	{
		UnSheathingEndNotify->OnNotified.AddDynamic(this, &APlayerCharacter::SheathingEndPlayer);
	}
	if (const TObjectPtr<UGrabWeaponNotify> GrabWeaponNotify =
		UAnimNotifyManager::FindNotifyByClass<UGrabWeaponNotify>(CombatComponent->GetUnSheathAnimMontage()))
	{
		GrabWeaponNotify->OnNotified.AddDynamic(this, &APlayerCharacter::UnSheathPlayer);
	}
	if (const TObjectPtr<UUnSheathingEndNotify> UnSheathingEndNotify =
		UAnimNotifyManager::FindNotifyByClass<UUnSheathingEndNotify>(CombatComponent->GetUnSheathAnimMontage()))
	{
		UnSheathingEndNotify->OnNotified.AddDynamic(this, &APlayerCharacter::SheathingEndPlayer);
	}
}

void APlayerCharacter::UnSheathPlayer()
{
	UWeaponManager::UnSheathCharacterWeapon(Cast<ACharacter>(this), CombatComponent->GetMainWeapon(), true);
	UWeaponManager::UnSheathCharacterWeapon(Cast<ACharacter>(this), CombatComponent->GetSubWeapon(), false);
}

void APlayerCharacter::SheathPlayer()
{
	UWeaponManager::SheathCharacterWeapon(Cast<ACharacter>(this), CombatComponent->GetMainWeapon(), true);
	UWeaponManager::SheathCharacterWeapon(Cast<ACharacter>(this), CombatComponent->GetSubWeapon(), false);
}

void APlayerCharacter::SheathingEndPlayer()
{
	AnimStatus = EPlayerAnimationStatus::Default;
}

void APlayerCharacter::ClearAnimMode()
{
	AnimStatus = EPlayerAnimationStatus::Default;
}

void APlayerCharacter::InitAttack(UAnimMontage* CurrentAnim)
{
	if (const TObjectPtr<UComboAttackStartNotify> AttackStartNotify =
		UAnimNotifyManager::FindNotifyByClass<UComboAttackStartNotify>(CurrentAnim))
	{
		AttackStartNotify->OnNotified.AddDynamic(this, &APlayerCharacter::ClearAnimMode);
	}
	PlayAnimMontage(CurrentAnim);
}

void APlayerCharacter::Attack()
{
	if (IsCombatMode && AnimStatus != EPlayerAnimationStatus::Attacking)
	{
		AnimStatus = EPlayerAnimationStatus::Attacking;
		CombatComponent->ComboAttack();
	}
}

void APlayerCharacter::OnAttackStart()
{
	switch (
		UWeaponManager::GetCharacterEquipStatus(CombatComponent->GetMainWeapon(), CombatComponent->GetSubWeapon()))
	{
		case EHandEquipStatus::Dual:
		case EHandEquipStatus::Empty:
		{
			if (CombatComponent->GetComboIndex() % 2 == 0)
			{
				CombatComponent->GetMainWeapon()->SetWeaponDamageable();
			} else
			{
				CombatComponent->GetSubWeapon()->SetWeaponDamageable();
			}
		}
		case EHandEquipStatus::OnlyMain:
		{
			CombatComponent->GetMainWeapon()->SetWeaponDamageable();
		}
		case EHandEquipStatus::OnlySub:
		{
			CombatComponent->GetSubWeapon()->SetWeaponDamageable();
		}
	}
}

void APlayerCharacter::OnAttackEnd()
{
	switch (
		UWeaponManager::GetCharacterEquipStatus(CombatComponent->GetMainWeapon(), CombatComponent->GetSubWeapon()))
	{
	case EHandEquipStatus::Dual:
	case EHandEquipStatus::Empty:
		{
			if (CombatComponent->GetComboIndex() % 2 == 0)
			{
				CombatComponent->GetMainWeapon()->UnsetWeaponDamageable();
			} else
			{
				CombatComponent->GetSubWeapon()->UnsetWeaponDamageable();
			}
		}
	case EHandEquipStatus::OnlyMain:
		{
			CombatComponent->GetMainWeapon()->UnsetWeaponDamageable();
		}
	case EHandEquipStatus::OnlySub:
		{
			CombatComponent->GetSubWeapon()->UnsetWeaponDamageable();
		}
	}
}

void APlayerCharacter::OnToggleCamera(EPlayerCameraStatus CameraStatus)
{
	switch (CameraStatus)
	{
		case EPlayerCameraStatus::First:
		{
			bUseControllerRotationYaw = true;
		}
		case EPlayerCameraStatus::Third:
		{
			bUseControllerRotationYaw = false;
		}
		default:
		{
			
		}
	}
}


void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (ADefaultPlayerState* PS = GetPlayerState<ADefaultPlayerState>())
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		// BaseCharacter에서도 init 과정은 있었지만 플레이어의 경우는 playerState가 적용될 때 owner에 playerState를 넣어준다.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (ADefaultPlayerState* PS = GetPlayerState<ADefaultPlayerState>())
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		// BaseCharacter에서도 init 과정은 있었지만 플레이어의 경우는 playerState가 적용될 때 owner에 playerState를 넣어준다.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

