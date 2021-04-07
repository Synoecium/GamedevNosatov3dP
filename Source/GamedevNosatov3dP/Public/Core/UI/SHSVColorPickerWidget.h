// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class GAMEDEVNOSATOV3DP_API SHSVColorPickerWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHSVColorPickerWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

protected:
	FLinearColor SelectedColor;

	TArray<FLinearColor> GetGradientColors();
	void OnHueValueChanged(float Value);
};
