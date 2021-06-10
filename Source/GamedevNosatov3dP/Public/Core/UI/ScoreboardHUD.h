// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ScoreboardWidget.h"
#include "GameFramework/HUD.h"
#include "ScoreboardHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API AScoreboardHUD : public AHUD
{
	GENERATED_BODY()

public:

	AScoreboardHUD(const FObjectInitializer & ObjectInitializer);
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	UScoreboardWidget* ScoreboardWidget = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UScoreboardWidget> ScoreboardClass;
};
