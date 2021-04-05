// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/MainMenuWidget.h"




#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBoxSlot.h"
#include "Kismet/ImportanceSamplingLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ButtonLoadGame)
	{
		ButtonLoadGame->OnReleased.AddDynamic(this, &UMainMenuWidget::OnLoadGame);
	}
	if (ButtonAddNewButton)
	{
		ButtonAddNewButton->OnReleased.AddDynamic(this, &UMainMenuWidget::OnAddNewButton);
	}
	
	MediaPlayer = NewObject<UMediaPlayer>(this);
	//UMediaSource* Source = NewObject<UMediaSource>()
	MediaPlayer->OpenUrl("file://E:/Temp/2_5251747685832067183.MP4");
	MediaTexture = NewObject<UMediaTexture>(this);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();

	if (BGImage)
	{
		BGImage->SetBrushResourceObject(MediaTexture);
	}
	else GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Image isnt loaded!"));
}

void UMainMenuWidget::OnLoadGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("OnLoadGame"));

}

void UMainMenuWidget::OnAddNewButton()
{
	if (ButtonClass)
	{
		//UUserWidget* Button = CreateWidget<UUserWidget>(this, ButtonClass);
		UButton* Button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
		UVerticalBoxSlot* SlotButton = MainVerticalBox->AddChildToVerticalBox(Button);
		SlotButton->SetPadding(FMargin(15.f));

		Button->OnReleased.AddDynamic(this, &UMainMenuWidget::OnAddNewButton);
		
	}
}
