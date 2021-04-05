// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"


#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSaveGame;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton* ButtonLoadGame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton* ButtonAddNewButton;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UVerticalBox* MainVerticalBox;	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ButtonClass;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* BGImage;
	
	UPROPERTY()
	UMediaPlayer* MediaPlayer;
	UPROPERTY()
	UMediaTexture* MediaTexture;

	
	
	UFUNCTION()
	void OnLoadGame();

	UFUNCTION()
	void OnAddNewButton();
};
