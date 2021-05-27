// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	SaveLoadInstance = NewObject<USaveLoadObject>();
	
	_DLCLoader = NewObject<UDLCLoader>(this, "DLC_Loader");

	VideoPlayerManager = NewObject<UVideoPlayerManager>(this);
	/*
	if (VideoConfig)
	{
		VideoPlayerManager->Init(VideoConfig);
		VideoPlayerManager->LoadTestVideoResources();
		VideoPlayerManager->PlayTestVideo();
	}
	*/
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

TArray<FMapInfo> UMyGameInstance::GetMapInfo()
{
	return _DLCLoader->GetMapsInfo();
}
