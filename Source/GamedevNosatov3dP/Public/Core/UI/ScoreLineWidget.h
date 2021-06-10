// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreLineWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UScoreLineWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerNameScore(FString PlayerName, int32 Score);

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* PlayerScoreTextBlock;
	
};
