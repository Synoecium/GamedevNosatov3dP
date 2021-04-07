// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class GAMEDEVNOSATOV3DP_API SSpectrumSVWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSpectrumSVWidget)
	{}
		SLATE_ATTRIBUTE(FLinearColor, SelectedColor)
	
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override;

protected:
	TAttribute<FLinearColor> SelectedColor;
	const FSlateBrush* SelectorImage;
	
	FLinearColor GetRightTopColor() const;
	FLinearColor GetRightTopColor1Par(float hue) const;
	FVector2D CalcRelativeSelectedPosition() const;
};
