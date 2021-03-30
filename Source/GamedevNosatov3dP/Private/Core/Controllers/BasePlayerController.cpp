// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Controllers/BasePlayerController.h"
#include "Core/Actors/BaseBuilding.h"
#include "Core/Actors/BaseUnit.h"
#include "EngineUtils.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
/*
	UWorld* CurrentWorld = GetWorld();
	for(TActorIterator<AActor>Itr(CurrentWorld);Itr;++Itr)
	{
		if(Cast<ABaseBuilding>(*Itr))
		{
			ABaseBuilding* CurrentBarracks = Cast<ABaseBuilding>(*Itr);
			CurrentBarracks->OnSpawnUnit().AddUObject(this, &ABasePlayerController::OnUnitCreated);
		}
	}
	*/
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAxis(FName("MoveForward"), this, &ABasePlayerController::OnMoveForward);
	//InputComponent->BindKey(EKeys::W, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnKeyPressed);
}

void ABasePlayerController::OnMoveForward(float AxisValue)
{
	UE_LOG(LogTemp, Warning, TEXT("We are walking forward the current value is %s"), *FString::SanitizeFloat(AxisValue));
}

void ABasePlayerController::OnKeyPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("We pressed W key"));
}
/*
void ABasePlayerController::OnUnitCreated(ABaseUnit* Unit)
{
	Possess(Unit);
}*/
