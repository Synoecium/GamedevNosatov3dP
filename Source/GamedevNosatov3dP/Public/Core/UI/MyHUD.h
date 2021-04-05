// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UENUM()
enum class EWidgetId : uint8
{
	MainMenu,
	SaveLoadScreen,
	Inventory
};

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	UUserWidget* AddWidget(EWidgetId WidgetId);

	UPROPERTY(EditDefaultsOnly)
	TMap<EWidgetId, TSubclassOf<UUserWidget>> WidgetClasses;
	
	
};
