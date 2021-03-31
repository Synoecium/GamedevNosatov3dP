// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	SaveLoadInstance = NewObject<USaveLoadObject>();
	
	
}

void UMyGameInstance::Save(APlayerController* Player)
{
	if (SaveLoadInstance)
	{
		SaveLoadInstance->SaveCharacter(Player);
	}
}

void UMyGameInstance::Load(APlayerController* Player)
{
	if (SaveLoadInstance)
	{
		SaveLoadInstance->LoadCharacter(Player);
	}
}
