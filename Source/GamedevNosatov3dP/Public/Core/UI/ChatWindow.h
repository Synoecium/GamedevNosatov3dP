// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"

#include "ChatWindow.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UChatWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	void AddMessage(FText Message);

protected:

	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox* ChatScrollBox;
	UPROPERTY(meta = (BindWidgetOptional))
	UEditableTextBox* NewMessageTextBox;
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* SendButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UChatMessage> MessageWidgetClass;

	UFUNCTION()
	void OnSendButtonClicked();

	UFUNCTION()
	void OnNewMessageCommited(const FText& NewMessage, ETextCommit::Type CommitType);
	
	UFUNCTION(BlueprintCallable)
	void SetFocusOnInput();
};
