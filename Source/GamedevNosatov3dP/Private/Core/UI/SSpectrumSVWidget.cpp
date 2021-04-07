// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/SSpectrumSVWidget.h"

#include "SlateOptMacros.h"
#include "Widgets/Colors/SSimpleGradient.h"
#include "Widgets/SOverlay.h"
//#include "Styling/CoreStyle.h"
#include "Core/UI/ColorPickerWidgetStyle.h"
#include "Core/UI/FStyleSet.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSpectrumSVWidget::Construct(const FArguments& InArgs)
{
	SelectedColor = InArgs._SelectedColor;
	//int32 hue = 240.f;
	SelectorImage = &FStyleSet::Get().GetWidgetStyle<FColorPickerStyle>("SWS_ColorPicker").SelectorImage;
	
	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay)
		+SOverlay::Slot()
		[
			SNew(SSimpleGradient)
			.StartColor(FLinearColor(1.f, 1.f, 1.f))
			//.EndColor(InArgs._SelectedColor)
			//.EndColor(MakeAttributeRaw<FLinearColor>(this, &SSpectrumSVWidget::GetRightTopColor1Par, hue))
			.EndColor(this, &SSpectrumSVWidget::GetRightTopColor)
			//.EndColor(GetRightTopColor())
			//.EndColor_Lambda([this, hue]() {return FLinearColor(hue, 1.f, 1.f, 1.f).HSVToLinearRGB();})
			.Orientation(EOrientation::Orient_Vertical)
		]
		+SOverlay::Slot()
		[
		    SNew(SSimpleGradient)
		    .StartColor(FLinearColor(0.f, 0.f, 0.f, 0.f))
		    .EndColor(FLinearColor(0.f, 0.f, 0.f))
		    .Orientation(EOrientation::Orient_Horizontal)
		]
	];
	
}

int32 SSpectrumSVWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	LayerId = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// draw selector
	LayerId++;
	//SColorSpectrum::CalcRelativeSelectedPosition()
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(CalcRelativeSelectedPosition() * AllottedGeometry.Size
			- SelectorImage->ImageSize * 0.5f, SelectorImage->ImageSize),
		SelectorImage
	);

	return LayerId;
}

FLinearColor SSpectrumSVWidget::GetRightTopColor() const
{
	float hue = SelectedColor.Get().R;
	return FLinearColor(hue, 1.f, 1.f, 1.f).HSVToLinearRGB();
}

FLinearColor SSpectrumSVWidget::GetRightTopColor1Par(float hue) const
{
	//float hue = SelectedColor.Get().R;
	return FLinearColor(hue, 1.f, 1.f, 1.f).HSVToLinearRGB();
}

FVector2D SSpectrumSVWidget::CalcRelativeSelectedPosition() const
{
	const FLinearColor& Color = SelectedColor.Get();
	return FVector2D(Color.G, 1.f - Color.B);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
