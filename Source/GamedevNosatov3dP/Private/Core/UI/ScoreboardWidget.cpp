// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/ScoreboardWidget.h"
#include "Core/UI/ScoreLineWidget.h"
#include "Core/BaseGameModeBase.h"

#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void UScoreboardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UScoreboardWidget::OnRestartButtonClicked);
	}
	LoadScoreboard();
}


void UScoreboardWidget::LoadScoreboard()
{
	if (!ScoreLineWidgetClass) return;
	TSubclassOf<UScoreLineWidget> WidgetClass = ScoreLineWidgetClass ? ScoreLineWidgetClass : TSubclassOf<UScoreLineWidget>(UScoreLineWidget::StaticClass());
	
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld==nullptr) return;
	ABaseGameModeBase* CurrentGameMode = Cast<ABaseGameModeBase>(UGameplayStatics::GetGameMode(CurrentWorld));
	if (CurrentGameMode==nullptr) return;
	//return;
	auto ScoreData = CurrentGameMode->GetUserData();
	for (auto ScoreEntry : ScoreData)
	{
		UScoreLineWidget* ScoreLineWidget = CreateWidget<UScoreLineWidget>(GetWorld(), WidgetClass);
		ScoreLineWidget->SetPlayerNameScore(ScoreEntry.Name, ScoreEntry.Scores);
		if (LinesVerticalBox)
		{
			LinesVerticalBox->AddChild(ScoreLineWidget);
		}
	}
}

void UScoreboardWidget::OnRestartButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Restarting game..."))
	if (OnRestartGame.IsBound())
	{
		OnRestartGame.Broadcast();
	}
}
