// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animations/BaseTestAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"

void UBaseTestAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	if (Owner)
	{
		if (Owner->IsA(AGamedevNosatov3dPCharacter::StaticClass()))
		{
			PlayerCharacter = Cast<AGamedevNosatov3dPCharacter>(Owner);
		}
	}
}

void UBaseTestAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// again check pointers
	if (PlayerCharacter)
	{
		auto Velocity = PlayerCharacter->GetVelocity();
		Speed = Velocity.Size();
		auto Transform = PlayerCharacter->GetTransform();
		auto RotAngle = Transform.InverseTransformVectorNoScale(Velocity).ToOrientationRotator();
		Angle = RotAngle.Yaw;
		FRotator AimRotation = PlayerCharacter->GetControlRotation() - PlayerCharacter->GetActorRotation();
		AimRotation.Normalize();
		AimPitch = AimRotation.Pitch;
		
		bIsInAir = PlayerCharacter->GetMovementComponent()->IsFalling();
		bIsAnimationBlended = PlayerCharacter->IsAnimationBlended();			
		bIsCrouching = PlayerCharacter->GetMovementComponent()->IsCrouching();
		bIsArmed = PlayerCharacter->IsArmed();
		bIsMoving = Speed > 0 ? true : false;

		KnockbackAngle = PlayerCharacter->KnockbackAngleValue;
	}
	
}
