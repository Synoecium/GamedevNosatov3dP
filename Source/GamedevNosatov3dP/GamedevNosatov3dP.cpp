// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamedevNosatov3dP.h"
#include "Modules/ModuleManager.h"

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, GamedevNosatov3dP, "GamedevNosatov3dP" );
IMPLEMENT_PRIMARY_GAME_MODULE( FGamedevNosatov3dP, GamedevNosatov3dP, "GamedevNosatov3dP" );

void FGamedevNosatov3dP::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();

	/*Loads resources and registers them with Slate*/
	/*Do this before trying to use resources*/
	MyUIResources.Initialize();

	/*TODO: Anything else game module might need to do on load*/
}

void FGamedevNosatov3dP::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();

	/*Unregister resources/styles with Slate, cleanup, free memory*/
	MyUIResources.Shutdown();

	/*Cleanup/free any resources here*/
}

/*First defined here, no need to call parent*/
/*Give caller a pointer to our FSlateGameResources*/
TSharedPtr<FSlateGameResources> FGamedevNosatov3dP::GetSlateGameResources()
{
	/*Give caller a pointer to our FSlateGameResources*/
	/*Giving strong pointer, helps gurantee access to resources*/
	return MyUIResources.GetSlateGameResources();
}