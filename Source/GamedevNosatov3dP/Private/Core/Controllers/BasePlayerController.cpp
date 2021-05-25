// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Controllers/BasePlayerController.h"
#include "Core/Actors/BaseBuilding.h"
#include "Core/Actors/BaseUnit.h"
#include "EngineUtils.h"
#include "Core/UI/MyHUD.h"
#include "Kismet/GameplayStatics.h"

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

	OnPlayerMissAim.AddUObject(this, &ABasePlayerController::ClearHitCounts);

	CurrentPlayerName = "Player" + FString::FromInt(FMath::RandHelper(10000));
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

void ABasePlayerController::ClearHitCounts()
{
	HitCountInRow = 0;
}

void ABasePlayerController::RegisterHitAim()
{
	HitCountInRow++;
	OnPlayerHitAim.Broadcast(HitCountInRow);
}

void ABasePlayerController::SendChatMessage_Implementation(const FText& Message)
{
	FText MessageWithName = FText::Format(NSLOCTEXT("MultyplayerChat", "Message", "{0}: {1}"),
		FText::FromString(CurrentPlayerName), Message);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePlayerController::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		ABasePlayerController* Controller = Cast<ABasePlayerController>(Actor);
		Controller->ReceiveMessage(MessageWithName);
	}

	
}

void ABasePlayerController::ReceiveMessage_Implementation(const FText& Message)
{
	AMyHUD* HUD = Cast<AMyHUD>(GetHUD());
	if (HUD)
	{
		HUD->AddMessageToChatWindow(Message);
	}
}

/*
void ABasePlayerController::OnUnitCreated(ABaseUnit* Unit)
{
	Possess(Unit);
}*/
