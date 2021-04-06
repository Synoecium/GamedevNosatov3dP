// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/SStandardSlateWidget.h"
#include "SlateOptMacros.h"
#include "Framework/Styling/ButtonWidgetStyle.h"
#include "Modules/ModuleManager.h"
#include "GamedevNosatov3dP/GamedevNosatov3dP.h"

#include "Styling/SlateStyleRegistry.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SStandardSlateWidget"

void SStandardSlateWidget::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUDArg;
	auto MyInCompositeFont = FCoreStyle::GetDefaultFont();
	FSlateFontInfo MyFont = FSlateFontInfo(MyInCompositeFont, 40);//second param is font size
	MyUIResources = FModuleManager::GetModuleChecked<FGamedevNosatov3dP>(FName("GamedevNosatov3dP")).GetSlateGameResources();
	
	const FSlateBrush *m_icon = MyUIResources->GetBrush(FName("SB_Spell_heal"));	
	
	if (m_icon==MyUIResources->GetDefaultBrush())
	{
		UE_LOG(LogTemp, Error, TEXT("Slate brush wasn't loaded!"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("Slate brush loaded - OK"));

	//No need to add a new slot, ChildSlot is one, 
	ChildSlot.VAlign(VAlign_Bottom).HAlign(HAlign_Center)
    [//start adding contents
        SNew(SOverlay)
        /* + operator adds a new slot */
        + SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
        [/* [ operator begins adding things to our new slot's contents */
            SNew(SHorizontalBox).Visibility(EVisibility::Visible)
            //Add slots to HorizontalBox, these will hold images
            + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
            [   //
                SNew(SImage).Image(m_icon)
            ]
            + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
            [
                SNew(SImage).Image(m_icon)
            ]
            + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
            [
                SNew(SImage).Image(m_icon)
            ]
            + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
            [
                SNew(SImage).Image(m_icon)
            ]
            + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom).AutoWidth()
            [
			    SNew(STextBlock)
			    .ShadowColorAndOpacity(FLinearColor::Black)
			    .ColorAndOpacity(FLinearColor::Red)
			    .ShadowOffset(FIntPoint(-1,1))
			    .Font(MyFont)
			    .Text(LOCTEXT("HelloSlateText", "Hello, Slate"))
			]
			+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom).AutoWidth()
			[
			    SNew(SButton)	
			    [
					SNew(STextBlock).Text(LOCTEXT("SlateButton","Slate button")).Font(MyFont)
			    ]
			]
			+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom).AutoWidth().Padding(10)
            [
                SNew(SEditableText).Font(MyFont).Text(LOCTEXT("SlateEditable","Slate editable"))
            ]
            + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom).AutoWidth().Padding(10)
            [
            	SNew(SBox).WidthOverride(400.f).HeightOverride(50.f)
            	[
            		SNew(SProgressBar).Percent(0.5f)
            	]

            ]
        ]//End slotting of SOverlay
    ];//End slotting ChildSlot
}

////////////////////////////////////////////////////////////////////////////////////////////////////
     /*FMyUIResources*//*FMyUIResources*//*FMyUIResources*//*FMyUIResources*//*FMyUIResources*/
////////////////////////////////////////////////////////////////////////////////////////////////////

void FMyUIResources::Initialize()
{
	if (!MyUIResources.IsValid())
	{
		MyUIResources = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MyUIResources);
	}
}

TSharedPtr<FSlateGameResources> FMyUIResources::GetSlateGameResources()
{
	return MyUIResources;
}

TSharedRef<class FSlateGameResources> FMyUIResources::Create()
{
	return FSlateGameResources::New(FName("MyUIResources"), m_Path, m_Path);
}

/*Unregister resources/styles with Slate, cleanup, free memory*/
void FMyUIResources::Shutdown()
{
	//Unregister *MyUIResources with Slate
	FSlateStyleRegistry::UnRegisterSlateStyle(*MyUIResources);

	//Debugging
	ensure(MyUIResources.IsUnique());

	//Removes reference to resources, decrements refcount, destroys resources if refcount=0
	//Do this to all SharedPtrs on Shutdown() or SomethingSimilar() to avoid memory leak
	MyUIResources.Reset();
}


#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
