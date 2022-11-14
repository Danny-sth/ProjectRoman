// Copyright by Danny Kudinov


#include "MainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bAlive = true;
	bThirdPersonCameraActive = true;
	bUseControllerRotationYaw = true;
	bWalking = false;
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AMainCharacter::Walk);
	PlayerInputComponent->BindAction("FirstPerson", IE_Pressed, this, &AMainCharacter::SwitchCamera);
}

void AMainCharacter::MoveForward(float Axis)
{
	if (bAlive)
	{
		AddMovementInput(GetActorForwardVector() * Axis);
	}
}

void AMainCharacter::MoveRight(float Axis)
{
	if (bAlive)
	{
		AddMovementInput(GetActorRightVector() * Axis);
	}
}

void AMainCharacter::Jump()
{
	if (bAlive)
	{
		Super::Jump();
	}
}

void AMainCharacter::Walk()
{
	if (bAlive)
	{
		if (bWalking)
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed * 2;
			bWalking = false;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed / 2;
			bWalking = true;
		}
	}
}

void AMainCharacter::SwitchCamera()
{
	if (bAlive)
	{
		if (bThirdPersonCameraActive)
		{
			CameraBoom->TargetArmLength = 0.0f;
			bThirdPersonCameraActive = false;
		}
		else
		{
			CameraBoom->TargetArmLength = 250.0f;
			bThirdPersonCameraActive = true;
		}
	}
}
