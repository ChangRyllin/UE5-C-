// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APCharacter::APCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));


	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const ULocalPlayer* Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (DefaultMapping)
		{
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}

	}
	
}

void APCharacter::Move(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator ControllerRotationOnlyY (0, Controller->GetControlRotation().Yaw, 0);
		const FVector FowardDirection(FRotationMatrix(ControllerRotationOnlyY).GetUnitAxis(EAxis::X));
		const FVector RinghtDirection(FRotationMatrix(ControllerRotationOnlyY).GetUnitAxis(EAxis::Y));
		AddMovementInput(FowardDirection, MoveVector.X);
		AddMovementInput(RinghtDirection, MoveVector.Y);

	}
}

void APCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookInput.X);
		AddControllerPitchInput(LookInput.Y);
	}
}


// Called every frame
void APCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APCharacter::Look);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APCharacter::Move);
	}

}

