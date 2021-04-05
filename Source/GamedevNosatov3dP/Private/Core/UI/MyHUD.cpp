// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/MyHUD.h"

#include "Blueprint/UserWidget.h"

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
