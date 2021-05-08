// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "DLCLoader.h"
#include "GamedevNosatov3dPCharacter.h"
#include "SaveLoadObject.h"
#include "Engine/GameInstance.h"
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

private:
	UPROPERTY()
	USaveLoadObject* SaveLoadInstance;

protected:
	UPROPERTY()
	UDLCLoader* _DLCLoader;
	
};
