// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/InputPlayerName.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "Core/BaseGameModeBase.h"

void UInputPlayerName::NativeConstruct()
{
	Super::NativeConstruct();

	if (SendButton)
	{
		SendButton->OnClicked.AddDynamic(this, &UInputPlayerName::OnSendButtonClicked);
	}
	if (PlayerNameEditable)
	{
		PlayerNameEditable->OnTextCommitted.AddDynamic(this, &UInputPlayerName::OnPlayerNameCommited);
	}
}

void UInputPlayerName::PostLoad()
{
	Super::PostLoad();

	//AddToViewport();
}

void UInputPlayerName::GetInput()
{
	SetVisibility(ESlateVisibility::Visible);
	if (!IsInViewport()) AddToViewport();
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld == nullptr) return;
	auto Controller = UGameplayStatics::GetPlayerController(CurrentWorld,0);
	if (Controller == nullptr) return;
	Controller->SetShowMouseCursor(true);
	FInputModeUIOnly InputMode;
	//FInputModeGameAndUI InputMode;
	Controller->SetInputMode(InputMode);
}

/*void UInputPlayerName::PlayerSentName_Implementation()
{
}*/

void UInputPlayerName::OnSendButtonClicked()
{
	if (PlayerNameEditable)
	{
		FText PlayerName = PlayerNameEditable->GetText();
		if (!PlayerName.IsEmpty())
		{
			//FText EmptyText;
			UWorld* CurrentWorld = GetWorld();
			if (CurrentWorld==nullptr) return;
			auto Controller = UGameplayStatics::GetPlayerController(CurrentWorld,0);
			if (Controller == nullptr) return;
			Controller->SetShowMouseCursor(false);
			FInputModeGameOnly InputMode;	
			Controller->SetInputMode(InputMode);
			ABaseGameModeBase* CurrentGameMode = Cast<ABaseGameModeBase>(UGameplayStatics::GetGameMode(CurrentWorld));
			if (CurrentGameMode==nullptr) return;
			float CurrentScore = CurrentGameMode->GetScore();
			CurrentGameMode->SavePlayerResult(PlayerName.ToString(), static_cast<int32>(CurrentScore));
			//PlayerSentName();
			if (OnPlayerSentName.IsBound())
			{
				OnPlayerSentName.Broadcast();
			}
		}
		//PlayerNameEditable->SetText(FText::GetEmpty());
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UInputPlayerName::OnPlayerNameCommited(const FText& NewMessage, ETextCommit::Type CommitType)
{
	if (CommitType == ETextCommit::OnEnter)
	{
		OnSendButtonClicked();		
	}
}
