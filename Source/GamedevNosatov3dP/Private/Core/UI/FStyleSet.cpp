﻿#include "Core/UI/FStyleSet.h"

#include "Slate/SlateGameResources.h"

TSharedPtr<ISlateStyle> FindStyle(const FString& ScopeToDirectory)
{
	TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("StyleSet"),
		ScopeToDirectory, ScopeToDirectory);

	return Style;
}

TSharedPtr<ISlateStyle> FStyleSet::StylePtr = NULL;

void FStyleSet::Initialize()
{
	Shutdown();

	StylePtr = FindStyle("/Game/UI/Styles");
	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void FStyleSet::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		ensure(StylePtr.IsUnique());
		StylePtr.Reset();
	}
	
}

const ISlateStyle& FStyleSet::Get()
{
	if (!StylePtr.IsValid())
	{
		Initialize();
	}
	return *StylePtr;
}
