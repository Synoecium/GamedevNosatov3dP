// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "DLCLoader.h"
#include "GamedevNosatov3dPCharacter.h"
#include "SaveLoadObject.h"
#include "Engine/GameInstance.h"
#include "VideoPlayer/VideoPlayerManager.h"

#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	void Save(APlayerController* Player);
	void Load(APlayerController* Player);

	UFUNCTION(BlueprintCallable)
	TArray<FMapInfo> GetMapInfo();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UVideoConfig> VideoConfig;

private:
	UPROPERTY()
	USaveLoadObject* SaveLoadInstance;

	UPROPERTY()
	UVideoPlayerManager* VideoPlayerManager;

protected:
	UPROPERTY()
	UDLCLoader* _DLCLoader;
	
};
