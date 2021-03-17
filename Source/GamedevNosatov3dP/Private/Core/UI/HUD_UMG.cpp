// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/HUD_UMG.h"

#include "PawnTurret.h"
#include "Core/BaseGameModeBase.h"
#include "Kismet/GameplayStatics.h"

//HUD_UMG.cpp
void UHUD_UMG::NativeConstruct()
{
	Super::NativeConstruct();

	if (TextScore)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Bind GetScoreText"));
		TextScore->TextDelegate.BindUFunction(this, "GetScoreText");
	}
	//HUD_UMG.cpp
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
}
//HUD_UMG.cpp
FText UHUD_UMG::GetScoreText()
{
	FText EmptyText;
	//UE_LOG(LogTemp, Warning, TEXT("UMG HUD: Binded function call"));
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld==nullptr) return EmptyText;
	ABaseGameModeBase* CurrentGameMode = Cast<ABaseGameModeBase>(UGameplayStatics::GetGameMode(CurrentWorld));
	if (CurrentGameMode==nullptr) return EmptyText;
	float CurrentScore = CurrentGameMode->GetScore();
	FString ScoreString = FString::Printf(TEXT("%d"), static_cast<int32>(CurrentScore));
	return FText::FromString(ScoreString);
	
}

void UHUD_UMG::OnTurretKilled()
{
	UE_LOG(LogTemp, Warning, TEXT("UMG HUD: Turret killed!"));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Turret killed!"));
	if (TextMessagePopup && TextEarnedScore)
	{
		//UE_LOG(LogTemp, Warning, TEXT("UMG HUD: Show Message"));
		FText NewMessage = FText::FromString(TEXT("Good job: turred killed!"));
		TextMessagePopup->SetText(NewMessage);

		UWorld* CurrentWorld = GetWorld();
		if (CurrentWorld)
		{
			ABaseGameModeBase* CurrentGameMode = Cast<ABaseGameModeBase>(UGameplayStatics::GetGameMode(CurrentWorld));
			if (CurrentGameMode)
			{
				FString EarnedScore = FString::Printf(TEXT("+%d"), static_cast<int32>(CurrentGameMode->ScoreForKillTurret));
				TextEarnedScore->SetText(FText::FromString(EarnedScore));				
			}
			CurrentWorld->GetTimerManager().ClearTimer(TimerHandleMessagePopup);
			CurrentWorld->GetTimerManager().SetTimer(TimerHandleMessagePopup, this, &UHUD_UMG::OnTimeMessageEnded, 2, false);
			
		}
	}
}

void UHUD_UMG::OnTimeMessageEnded()
{
	if (TextMessagePopup)
	{
		TextMessagePopup->SetText(FText());
		TextEarnedScore->SetText(FText());
	}
	
}
