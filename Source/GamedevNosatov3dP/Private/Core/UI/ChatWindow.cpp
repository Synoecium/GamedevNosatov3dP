// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/ChatWindow.h"

#include "Core/Controllers/BasePlayerController.h"
#include "Core/UI/ChatMessage.h"

void UChatWindow::NativeConstruct()
{
	Super::NativeConstruct();

	if (SendButton)
	{
		SendButton->OnClicked.AddDynamic(this, &UChatWindow::OnSendButtonClicked);
	}
	if (NewMessageTextBox)
	{
		NewMessageTextBox->OnTextCommitted.AddDynamic(this, &UChatWindow::OnNewMessageCommited);
	}
}

void UChatWindow::AddMessage(FText Message)
{
	TSubclassOf<UChatMessage> WidgetClass = MessageWidgetClass ? MessageWidgetClass : TSubclassOf<UChatMessage>(UChatMessage::StaticClass());
	UChatMessage* NewMessageWidget = CreateWidget<UChatMessage>(GetWorld(), WidgetClass);
	NewMessageWidget->SetMessageText(Message);
	if (ChatScrollBox)
	{
		ChatScrollBox->AddChild(NewMessageWidget);
	}
}

void UChatWindow::OnSendButtonClicked()
{
	if (NewMessageTextBox)
	{
		FText Message = NewMessageTextBox->GetText();
		if (!Message.IsEmpty())
		{
			ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
			PlayerController->SendChatMessage(Message);
		}
		NewMessageTextBox->SetText(FText::GetEmpty());
	}
}

void UChatWindow::OnNewMessageCommited(const FText& NewMessage, ETextCommit::Type CommitType)
{
	if (CommitType == ETextCommit::OnEnter)
	{
		OnSendButtonClicked();
		NewMessageTextBox->SetFocus();		
	}
}

void UChatWindow::SetFocusOnInput()
{
	NewMessageTextBox->SetFocus();
}

