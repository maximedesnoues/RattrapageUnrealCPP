// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_DesnouesMaxime : ModuleRules
{
	public FPS_DesnouesMaxime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
