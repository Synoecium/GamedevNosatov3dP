// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/ScoreboardHUD.h"

#include "Kismet/GameplayStatics.h"

AScoreboardHUD::AScoreboardHUD(const FObjectInitializer& ObjectInitializer) : AHUD(ObjectInitializer)
{

}

void AScoreboardHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld == nullptr) return;
	auto Controller = UGameplayStatics::GetPlayerController(CurrentWorld,0);
	if (Controller == nullptr) return;
	Controller->SetShowMouseCursor(true);
	FInputModeUIOnly InputMode;
	Controller->SetInputMode(InputMode);
	
	if (ScoreboardClass)
	{
		ScoreboardWidget = CreateWidget<UScoreboardWidget>(CurrentWorld
			, ScoreboardClass ? ScoreboardClass : TSubclassOf<UScoreboardWidget>(UScoreboardWidget::StaticClass()));
	}
	if (ScoreboardWidget)
	{
		ScoreboardWidget->AddToViewport();
	}
}
