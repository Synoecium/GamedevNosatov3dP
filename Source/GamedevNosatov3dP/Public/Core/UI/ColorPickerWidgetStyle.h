// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "ColorPickerWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct GAMEDEVNOSATOV3DP_API FColorPickerStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FColorPickerStyle();
	virtual ~FColorPickerStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FColorPickerStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category="Appearance")
	FSlateBrush SelectorImage;
	
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UColorPickerWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FColorPickerStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
