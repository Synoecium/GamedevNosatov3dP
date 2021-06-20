// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GamedevNosatov3dPCharacter.h"
#include "Animation/AnimInstance.h"
#include "BaseTestAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UBaseTestAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	UPROPERTY(BlueprintReadWrite)
	bool bIsShooting;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInAir;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAnimationBlended;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCrouching;

	UPROPERTY(BlueprintReadWrite)
	bool bIsArmed;

	UPROPERTY(BlueprintReadWrite)
	bool bIsMoving;

	UPROPERTY(BlueprintReadWrite)
	float Angle;

	UPROPERTY(BlueprintReadWrite)
	float Speed;

	UPROPERTY(BlueprintReadWrite)
	float AimPitch;

	UPROPERTY(BlueprintReadWrite)
	float KnockbackAngle;
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	APawn* Owner = nullptr;
	AGamedevNosatov3dPCharacter* PlayerCharacter = nullptr;
	
};
