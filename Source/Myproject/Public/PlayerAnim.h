// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

class APCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation()override;
	virtual void NativeUpdateAnimation(float  DeltaSeconds)override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APCharacter>PlayerCharacter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent>PlayerCharacterMovement;

	UPROPERTY(BlueprintReadOnly)
	float speed;

};
