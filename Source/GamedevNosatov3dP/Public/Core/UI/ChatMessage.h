// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "ChatMessage.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UChatMessage : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMessageText(FText NewText);

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* MessageText;
	
};
