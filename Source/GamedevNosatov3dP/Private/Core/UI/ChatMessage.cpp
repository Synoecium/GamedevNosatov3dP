// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/ChatMessage.h"

void UChatMessage::SetMessageText(FText NewText)
{
	if (MessageText)
	{
		MessageText->SetText(NewText);
	}
}
