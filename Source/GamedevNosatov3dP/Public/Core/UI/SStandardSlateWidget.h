// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Slate/SlateGameResources.h"
#include "Widgets/Notifications/SProgressBar.h"

class FMyUIResources
{
public:
	FMyUIResources() : m_Path("/Game/UI"), MyUIResources(NULL) { } ;

	/*Loads resources and registers them with Slate*/
	/*Do this before trying to use resources*/
	void Initialize();

	/*cleanup*/
	/*Do this when shutting down game module*/
	void Shutdown();

	/*reloads textures used by slate renderer*/
	/*Does nothing at the moment*/
	void ReloadTextures();

	/*Give caller a pointer to our FSlateGameResources*/
	TSharedPtr<FSlateGameResources> GetSlateGameResources();

protected:
	/*Creates resources*/
	TSharedRef<class FSlateGameResources> Create();

	/*Defined in Cpp file, change as needed*/
	const FString m_Path;

	/*Poitner to game resources, Initialize() before using*/
	TSharedPtr<FSlateGameResources> MyUIResources;
};

/**
 * 
 */
class GAMEDEVNOSATOV3DP_API SStandardSlateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStandardSlateWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AStandardHUD>, OwnerHUDArg);
	
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TWeakObjectPtr<class AStandardHUD> OwnerHUD;
	TSharedPtr<FSlateGameResources> MyUIResources;
};
