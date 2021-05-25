// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "Core/Controllers/BasePlayerController.h"
#include "Core/UI/SHSVColorPickerWidget.h"
#include "Core/UI/SSpectrumSVWidget.h"
#include "Kismet/GameplayStatics.h"

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
/*	//Slate color picker
	GEngine->GameViewport->AddViewportWidgetContent(
		SNew(SHSVColorPickerWidget)
		//.SelectedColor(FLinearColor(120.f, 0.8f, 0.9f))
	);
*/

	if (HitComboWidgetClass)
	{
		HitComboWidget = CreateWidget<UHitComboWidget>(GetWorld(), HitComboWidgetClass);
		/** Make sure widget class created */
		if (HitComboWidget)
		{
			/** Add it to the viewport */
			HitComboWidget->AddToViewport();
		}
	}

	auto playerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	playerController->OnPlayerHitAim.AddUObject(this, &AMyHUD::UpdateComboCount);
	playerController->OnPlayerMissAim.AddUObject(this, &AMyHUD::ResetCombo);

	ChatWindow = CreateWidget<UChatWindow>(GetWorld(), ChatWindowClass ? ChatWindowClass : UChatWindow::StaticClass());
	ChatWindow->AddToViewport();
	ChatWindow->SetVisibility(ESlateVisibility::Hidden);
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMyHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HitComboWidget)
	{
		
	}
}

void AMyHUD::UpdateComboCount(int32 Value)
{
	if (HitComboWidget)
	{
		HitComboWidget->UpdateComboCount(Value);
	}
}

void AMyHUD::ResetCombo()
{
	if (HitComboWidget)
	{
		HitComboWidget->ResetCombo();
	}
}

void AMyHUD::AddMessageToChatWindow(const FText& Message)
{
	if (ChatWindow)
	{
		ChatWindow->AddMessage(Message);
	}
}
