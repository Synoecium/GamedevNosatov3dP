// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "Core/UI/SHSVColorPickerWidget.h"
#include "Core/UI/SSpectrumSVWidget.h"

UUserWidget* AMyHUD::AddWidget(EWidgetId WidgetId)
{
	TSubclassOf<UUserWidget>* widgetClass = WidgetClasses.Find(WidgetId);
	if (widgetClass)
	{
		UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), *widgetClass);
		widget->AddToViewport();
		return widget;
	}
	return nullptr;
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	GEngine->GameViewport->AddViewportWidgetContent(
		SNew(SHSVColorPickerWidget)
		//.SelectedColor(FLinearColor(120.f, 0.8f, 0.9f))
	);
	
}
