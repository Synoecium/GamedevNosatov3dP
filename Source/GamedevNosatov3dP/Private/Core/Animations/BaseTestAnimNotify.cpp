// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animations/BaseTestAnimNotify.h"

#include "Kismet/GameplayStatics.h"

void UBaseTestAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Purple, __FUNCTION__);
	UWorld* CurrentWorld = MeshComp->GetWorld();
	if (CurrentWorld && ReloadSound)
	{
		UGameplayStatics::PlaySound2D(CurrentWorld, ReloadSound);
	}
}
