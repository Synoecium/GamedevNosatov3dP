// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/BaseGameModeBase.h"
#include "GamedevNosatov3dPCharacter.h"
#include "PawnTurret.h"
#include "Core/PawnBase.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABaseGameModeBase::ABaseGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	AmountOfMoney = 100;
	bEnableDance = false;
	DialogMessage = "Hello, I love dancing!";
	Base_ConfRef = nullptr;
	Score = 0.f;
}

bool ABaseGameModeBase::SpawnUnit(AActor*& parActor) 
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

void ABaseGameModeBase::Init_Implementation() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Init c++ Native Event"));
}

void ABaseGameModeBase::BeginPlay() 
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %i"), AmountOfMoney);

	for (auto& str : Names)
	{
		//UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %s"), *str);
	}

	if (ConfigurationClass)
	{
		Base_ConfRef = NewObject<UBaseUnitConfig>(this,ConfigurationClass);
		/*UE_LOG(LogTemp, Warning, TEXT("This is my log value 1: %i"), Base_ConfRef->ConfigValue1);
		UE_LOG(LogTemp, Warning, TEXT("This is my log value 2: %i"), Base_ConfRef->ConfigValue2);
		UE_LOG(LogTemp, Warning, TEXT("This is my log value 3: %i"), Base_ConfRef->ConfigValue3);*/
	}
	//PZ #5 start
	TArray<AActor*> turretActors;
	UGameplayStatics::GetAllActorsOfClass(this, APawnTurret::StaticClass(), turretActors);
	for (AActor* turretActor:turretActors)
	{
		APawnTurret* turret = Cast<APawnTurret>(turretActor);
		if (turret)
		{
			turret->OnPawnKilled.AddUFunction(this, "OnTurretKilled");
		}
	}
	//PZ #5 finish
	
	Init();
}

//PZ #5 start
void ABaseGameModeBase::OnTurretKilled()
{
	Score+=50.f;
}
//PZ #5 finish