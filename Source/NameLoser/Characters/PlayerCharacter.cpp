// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "NameLoser/Weapon/WeaponBase.h"

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
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
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

	// TODO: 추후 웨폰 등록시의 UI에 대한 반응으로 함수 따로 빼서 사용할 예정
	if (IsValid(RightWeapon))
	{
		RightWeaponData = GetWorld()->SpawnActor<AWeaponBase>(RightWeapon);
		if (IsValid(RightWeaponData))
		{
			RightWeaponData->GetWeaponMesh()->AttachToComponent(
					GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
					"weapon_inv_right"
				);
		}
	}

	// TODO: 추후 함수화해도 무방할듯
	UAnimInstance* PAnimInst = GetMesh()->GetAnimInstance();

	if (IsValid(PAnimInst))
	{
		PAnimInst->OnPlayMontageNotifyBegin.AddDynamic(this, &APlayerCharacter::StartDrawWeaponMontageNotifyBegin);
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
		EnhancedInputComponent->BindAction(DrawWeaponAction, ETriggerEvent::Started, this, &APlayerCharacter::StartDrawWeapon);
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
	GetCharacterMovement()->MaxWalkSpeed = IsRunning ? 700.f : 350.f;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
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

		AddMovementInput(ForwardDirection, static_cast<float>(MovementVector.Y));
		AddMovementInput(RightDirection, static_cast<float>(MovementVector.X));
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

void APlayerCharacter::StartDrawWeapon()
{
	
	if (IsCombatMode)
	{
		AnimStatus = Sheathing;
		IsCombatMode = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bUseControllerRotationYaw = GetIsFirstPersonView();
	} else
	{
		AnimStatus = Drawing;
		IsCombatMode = true;
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;

		if (UAnimInstance* AnimInst = GetMesh()->GetAnimInstance())
		{
			AnimInst->Montage_Play(DrawAnimationMontage);
		}
	}
	AnimStatus = Default;
}

void APlayerCharacter::StartDrawWeaponMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	RightWeaponData->GetWeaponMesh()->AttachToComponent(
        	GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
        	"weapon_r"
        );
}


UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}