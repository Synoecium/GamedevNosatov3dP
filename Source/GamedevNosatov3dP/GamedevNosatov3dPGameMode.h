// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamedevNosatov3dPGameMode.generated.h"

UCLASS(minimalapi)
class AGamedevNosatov3dPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGamedevNosatov3dPGameMode();

	UPROPERTY(EditAnyWhere, Category = "Bank | Money | USD")
	int32 AmountOfMoney;

	UPROPERTY(EditAnyWhere)
	bool bEnableDance;

	UPROPERTY(EditAnyWhere)
	FString DialogMessage;

	UPROPERTY(EditAnyWhere)
	TArray<FString> Names;

	UPROPERTY(EditAnyWhere)
	TSubclassOf<AActor> Unit;

	void BeginPlay() override;
};



