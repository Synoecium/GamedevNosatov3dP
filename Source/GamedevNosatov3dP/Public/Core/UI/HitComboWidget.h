// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitComboWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UHitComboWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UHitComboWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	
	void UpdateComboCount(int32 Value);
	void ResetCombo();
	void StoreWidgetAnimations();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTCombo;

private:
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* ComboFadeAnimation;
	UWidgetAnimation* ComboShakeAnimation;
	
};
