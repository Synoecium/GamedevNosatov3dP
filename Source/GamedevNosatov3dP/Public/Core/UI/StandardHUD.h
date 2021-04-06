// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/HUD.h"
#include "StandardHUD.generated.h"

class SStandardSlateWidget;
/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API AStandardHUD : public AHUD
{
	GENERATED_BODY()

public:
	TSharedPtr<SStandardSlateWidget> MyUIWidget;

	virtual void BeginPlay() override;	
	
};
