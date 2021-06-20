// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class GamedevNosatov3dP : ModuleRules
{
	public GamedevNosatov3dP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Public")
			// ... add public include paths required here ...
		});
		
		PrivateIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Private")
			//"/Source/Runtime/Launch/Private"
			// ... add other private include paths required here ... 

		});

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"
			//, "CustomBPDetailsBtn"
			, "AIModule", "GameplayTasks", "ProceduralMeshComponent", "ApexDestruction", "Sockets", "Networking" });
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate", "SlateCore", "UMG", "MediaAssets", "AppFramework", "PakFile", "DesktopPlatform"
			
		});

		//PrivateIncludePaths.AddRange(new string[] {"Plugins", "Plugins/MovieScene", "Plugins/SequencerScripting"});
		
		DynamicallyLoadedModuleNames.AddRange(new string[]
		{
			// ... add any modules that your module loads dynamically here ...
		});

		if (Target.Type == TargetRules.TargetType.Editor)
		{
			PublicDependencyModuleNames.AddRange(new string[]{"UnrealEd", "PropertyEditor"});
		}
	}
}
