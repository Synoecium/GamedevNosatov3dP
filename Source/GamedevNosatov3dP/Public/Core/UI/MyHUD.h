// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HitComboWidget.h"
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

	virtual void BeginPlay() override;

	//Primary draw call for the HUD.
	virtual void DrawHUD() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateComboCount(int32 Value);

	UFUNCTION()
	void ResetCombo();
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EWidgetId, TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY(EditDefaultsOnly, Category="Interactive")
	TSubclassOf<UUserWidget> HitComboWidgetClass;

private:
	UHitComboWidget* HitComboWidget;
	
	
};
