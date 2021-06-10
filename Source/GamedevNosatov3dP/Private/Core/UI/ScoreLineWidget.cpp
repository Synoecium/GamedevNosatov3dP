// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/ScoreLineWidget.h"

#include "Components/TextBlock.h"

void UScoreLineWidget::SetPlayerNameScore(FString PlayerName, int32 Score)
{
	PlayerNameTextBlock->SetText(FText::FromString(PlayerName));
	PlayerScoreTextBlock->SetText(FText::FromString(FString::FromInt(Score)));
}
