// Copyright by Danny Kudinov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include  "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class PROJECTROMAN_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CameraBoom")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CameraComponent")
	UCameraComponent* CameraComponent;

private:
	bool bAlive;
	bool bWalking;
	bool bThirdPersonCameraActive;
	float WalkSpeed;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	virtual void Jump() override;
	void Walk();
	void SwitchCamera();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
