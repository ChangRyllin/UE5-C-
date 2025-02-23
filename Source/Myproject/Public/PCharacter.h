// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class MYPROJECT_API APCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	//camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent>CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent>PlayerCamera;


	//input
	UPROPERTY(EditDefaultsOnly, Category = "input")
	TObjectPtr<UInputMappingContext>DefaultMapping;

	UPROPERTY(EditDefaultsOnly, Category = "input")
	TObjectPtr<UInputAction>MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "input")
	TObjectPtr<UInputAction>LookAction;


public:
	// Sets default values for this character's properties
	APCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
