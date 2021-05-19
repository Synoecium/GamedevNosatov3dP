// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Sound/SoundWave.h"
#include "BaseTestAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UBaseTestAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	USoundWave* BeginSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* EndSound = nullptr;	

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	int32 _FrameCount = 0;
	
};
