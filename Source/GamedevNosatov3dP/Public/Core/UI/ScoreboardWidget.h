// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "ScoreboardWidget.generated.h"

class UButton;
class UVerticalBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestartGameSignature);

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UScoreboardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void LoadScoreboard();

	UPROPERTY(BlueprintAssignable)
	FRestartGameSignature OnRestartGame;
	
protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UVerticalBox* LinesVerticalBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UScoreLineWidget> ScoreLineWidgetClass;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* RestartButton;

	UFUNCTION()
	void OnRestartButtonClicked();
	
};
