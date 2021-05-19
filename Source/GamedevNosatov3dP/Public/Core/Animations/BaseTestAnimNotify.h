// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Sound/SoundCue.h"
#include "BaseTestAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UBaseTestAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	USoundCue* ReloadSound = nullptr;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
