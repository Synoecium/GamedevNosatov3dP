// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputPlayerName.generated.h"

class UButton;
class UEditableTextBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerSentNameSignature);

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UInputPlayerName : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void PostLoad() override;

	UFUNCTION(BlueprintCallable)
	void GetInput();

	UPROPERTY(BlueprintAssignable)
	FPlayerSentNameSignature OnPlayerSentName;

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//void PlayerSentName();
	
protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UEditableTextBox* PlayerNameEditable;
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* SendButton;

	UFUNCTION()
	void OnSendButtonClicked();

	UFUNCTION()
	void OnPlayerNameCommited(const FText& NewMessage, ETextCommit::Type CommitType);
};
