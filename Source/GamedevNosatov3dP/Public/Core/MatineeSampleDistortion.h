// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "MatineeSampleDistortion.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UMatineeSampleDistortion : public UMatineeCameraShake
{
	GENERATED_BODY()
	
public:

	UMatineeSampleDistortion(const FObjectInitializer& ObjectInitializer);

	FVector2D AmplitudeRange = FVector2D(.5f,10.f);
	FVector2D FrequencyRange = FVector2D(20.f,35.f);	
	
};
