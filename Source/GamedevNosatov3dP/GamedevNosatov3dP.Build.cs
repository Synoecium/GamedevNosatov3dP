// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamedevNosatov3dP : ModuleRules
{
	public GamedevNosatov3dP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "CustomBPDetailsBtn",
		    "AIModule", "GameplayTasks", "ProceduralMeshComponent"});
		
		PrivateDependencyModuleNames.AddRange(new string[]{"Slate", "SlateCore", "UMG", "MediaAssets", "AppFramework", "PakFile", "DesktopPlatform"});

		if (Target.Type == TargetRules.TargetType.Editor)
		{
			PublicDependencyModuleNames.AddRange(new string[]{"UnrealEd"});
		}
	}
}
