// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamedevNosatov3dPGameMode.h"
#include "GamedevNosatov3dPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGamedevNosatov3dPGameMode::AGamedevNosatov3dPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	AmountOfMoney = 100;
	bEnableDance = false;
	DialogMessage = "Hello, I love dancing!";
}

void AGamedevNosatov3dPGameMode::BeginPlay() 
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %i"), AmountOfMoney);

	for (auto& str : Names)
	{
		UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %s"), *str);
	}

	UWorld* CurrentWorld = GetWorld();

	if (CurrentWorld) CurrentWorld->SpawnActor<AActor>(Unit);
}
