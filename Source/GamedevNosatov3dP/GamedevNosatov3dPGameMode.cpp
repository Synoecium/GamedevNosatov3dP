// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamedevNosatov3dPGameMode.h"
#include "GamedevNosatov3dPCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Core/BaseCoreConfig.h"

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
	Base_ConfRef = nullptr;
}

bool AGamedevNosatov3dPGameMode::SpawnUnit(AActor*& parActor) 
{
	UWorld* CurrentWorld = GetWorld();

	if (CurrentWorld && Unit) 
	{
		parActor = CurrentWorld->SpawnActor<AActor>(Unit);
		UE_LOG(LogTemp, Warning, TEXT("Spawn actor: %s"), *parActor->GetName());		
		BP_UpdateInfo();		 
		return true;
	}

	return false;
}

void AGamedevNosatov3dPGameMode::Init_Implementation() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Init c++ Native Event"));
}

void AGamedevNosatov3dPGameMode::BeginPlay() 
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %i"), AmountOfMoney);

	for (auto& str : Names)
	{
		UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %s"), *str);
	}

	if (ConfigurationClass)
	{
		Base_ConfRef = NewObject<UBaseCoreConfig>(this,ConfigurationClass);
		UE_LOG(LogTemp, Warning, TEXT("This is my log value 1: %i"), Base_ConfRef->ConfigValue1);
		UE_LOG(LogTemp, Warning, TEXT("This is my log value 2: %i"), Base_ConfRef->ConfigValue2);
		UE_LOG(LogTemp, Warning, TEXT("This is my log value 3: %i"), Base_ConfRef->ConfigValue3);
	}
	
	Init();
}
