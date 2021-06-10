// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamedevNosatov3dP : ModuleRules
{
	public GamedevNosatov3dP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"
			//, "CustomBPDetailsBtn"
			, "AIModule", "GameplayTasks", "ProceduralMeshComponent", "ApexDestruction", "Sockets", "Networking" });
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate", "SlateCore", "UMG", "MediaAssets", "AppFramework", "PakFile", "DesktopPlatform"
			
		});
		
		//PrivateIncludePaths.AddRange(new string[] {"Plugins", "Plugins/MovieScene", "Plugins/SequencerScripting"});

		if (Target.Type == TargetRules.TargetType.Editor)
		{
			PublicDependencyModuleNames.AddRange(new string[]{"UnrealEd", "PropertyEditor"});
		}
	}
}
