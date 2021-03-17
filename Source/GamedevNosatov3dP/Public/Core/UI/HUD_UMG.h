// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "HUD_UMG.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UHUD_UMG : public UUserWidget
{
	GENERATED_BODY()

public:
	//HUD_UMG.h
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextScore = nullptr;
	//HUD_UMG.h
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextMessagePopup = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextEarnedScore = nullptr;
	
public:
	virtual void NativeConstruct() override;
	//HUD_UMG.h
	UFUNCTION(BlueprintGetter)
	FText GetScoreText();

	UFUNCTION()
	void OnTurretKilled();



private:
	//HUD_UMG.h
	UFUNCTION()
	void OnTimeMessageEnded();

	FTimerHandle TimerHandleMessagePopup;
};
