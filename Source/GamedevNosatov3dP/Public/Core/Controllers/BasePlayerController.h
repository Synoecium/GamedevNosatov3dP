// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/Interfaces/Saveable.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */

DECLARE_EVENT_OneParam(ABasePlayerController, FOnPlayerHitAim, int32);
DECLARE_MULTICAST_DELEGATE(FOnPlayerMissAim);


UCLASS()
class GAMEDEVNOSATOV3DP_API ABasePlayerController : public APlayerController, public ISaveable
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnMoveForward(float AxisValue);

	UFUNCTION()
	void OnKeyPressed();

	//UFUNCTION()
	//void OnUnitCreated(class ABaseUnit* Unit);

	FOnPlayerHitAim OnPlayerHitAim;
	FOnPlayerMissAim OnPlayerMissAim;

	UFUNCTION()
	void ClearHitCounts();

	void RegisterHitAim();

	UFUNCTION(Server, Reliable)
	void SendChatMessage(const FText& Message);

	UFUNCTION(Client, Reliable)
	void ReceiveMessage(const FText& Message);

private:
	int32 HitCountInRow = 0;

protected:
	FString CurrentPlayerName;
	
};
