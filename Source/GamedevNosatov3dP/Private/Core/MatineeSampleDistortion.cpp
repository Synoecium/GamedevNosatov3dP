// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MatineeSampleDistortion.h"

UMatineeSampleDistortion::UMatineeSampleDistortion(const FObjectInitializer& ObjectInitializer) : UMatineeCameraShake(ObjectInitializer)
{
	//Время колебания
	OscillationDuration = 0.25f;

	//Время бленда
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	//Амплитуда поворота по Pitch Yaw
	RotOscillation.Pitch.Amplitude = FMath::RandRange(AmplitudeRange.X, AmplitudeRange.Y);
	RotOscillation.Pitch.Frequency = FMath::RandRange(FrequencyRange.X, FrequencyRange.Y);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(AmplitudeRange.X, AmplitudeRange.Y);
	RotOscillation.Yaw.Frequency = FMath::RandRange(FrequencyRange.X, FrequencyRange.Y);

	UE_LOG(LogTemp, Warning, TEXT("Construction of Shake, Pitch Ampl = %f, Pitch Freq = %f, Yaw Ampl = %f, Pitch Yaw = %f")
		, RotOscillation.Pitch.Amplitude, RotOscillation.Pitch.Frequency, RotOscillation.Yaw.Amplitude, RotOscillation.Yaw.Frequency);
}
