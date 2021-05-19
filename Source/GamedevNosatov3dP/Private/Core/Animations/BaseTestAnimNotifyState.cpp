// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animations/BaseTestAnimNotifyState.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

void UBaseTestAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration)
{
	_FrameCount = 0;
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, __FUNCTION__);

	UWorld* CurrentWorld = MeshComp->GetWorld();
	if (CurrentWorld && BeginSound)
	{
		UGameplayStatics::PlaySound2D(CurrentWorld, BeginSound);
	}
}

void UBaseTestAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	_FrameCount++;
}

void UBaseTestAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	auto mes = FString::Printf(TEXT(". From begin to end %d frames"),_FrameCount);
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, __FUNCTION__ + mes);

	UWorld* CurrentWorld = MeshComp->GetWorld();
	if (CurrentWorld && EndSound)
	{
		UGameplayStatics::PlaySound2D(CurrentWorld, EndSound);
	}
}
