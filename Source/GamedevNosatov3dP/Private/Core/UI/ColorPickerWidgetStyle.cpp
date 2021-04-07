// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/ColorPickerWidgetStyle.h"

FColorPickerStyle::FColorPickerStyle()
{
}

FColorPickerStyle::~FColorPickerStyle()
{
}

const FName FColorPickerStyle::TypeName(TEXT("FColorPickerStyle"));

const FColorPickerStyle& FColorPickerStyle::GetDefault()
{
	static FColorPickerStyle Default;
	return Default;
}

void FColorPickerStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

