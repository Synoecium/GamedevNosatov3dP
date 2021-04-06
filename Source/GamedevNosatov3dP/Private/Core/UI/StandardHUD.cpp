// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/StandardHUD.h"
#include "Core/UI/SStandardSlateWidget.h"
#include "Widgets/SWeakWidget.h"

void AStandardHUD::BeginPlay()
{
	MyUIWidget = SNew(SStandardSlateWidget).OwnerHUDArg(this);
	GEngine->GameViewport->AddViewportWidgetContent(
		SNew(SWeakWidget)
		.PossiblyNullContent(MyUIWidget.ToSharedRef())
	);
	MyUIWidget->SetVisibility(EVisibility::Visible);
	
}
