// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/SHSVColorPickerWidget.h"
#include "SlateOptMacros.h"
#include "Core/UI/SSpectrumSVWidget.h"
#include "Widgets/Colors/SComplexGradient.h"
#include "Widgets/Input/SSlider.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SHSVColorPickerWidget::Construct(const FArguments& InArgs)
{
	SelectedColor = FLinearColor(60.f, 0.8, 0.7f);
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		[
			SNew(SSpectrumSVWidget)
			.SelectedColor_Lambda([this]()->FLinearColor{ return SelectedColor;})

		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(0.f, 5.f, 0.f, 5.f))
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.HeightOverride(10.f)
				[
					SNew(SComplexGradient)
					.GradientColors(GetGradientColors())
				]
			]
			+SOverlay::Slot()
			.VAlign(VAlign_Center)
			.Padding(FMargin(-7.f, 0.f))
			[
				SNew(SSlider)
				.SliderBarColor(FLinearColor(0.f, 0.f, 0.f, 0.f))
				.OnValueChanged(this, &SHSVColorPickerWidget::OnHueValueChanged)
				.Value_Lambda([this]() -> float { return SelectedColor.R / 359.f; })
			]
		]
	];
}

TArray<FLinearColor> SHSVColorPickerWidget::GetGradientColors()
{
	TArray<FLinearColor> HueGradientColors;

	for (int32 i = 0; i<7; i++)
	{
		HueGradientColors.Add(FLinearColor((i%6) * 60.f, 1.f, 1.f).HSVToLinearRGB());
	}

	return HueGradientColors;

}

void SHSVColorPickerWidget::OnHueValueChanged(float Value)
{
	SelectedColor.R = Value * 359.f;
	GEngine->AddOnScreenDebugMessage(-1, 2, SelectedColor.HSVToLinearRGB().ToFColor(true), "NewColor");
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
