// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZadanieRekrutacyjne : ModuleRules
{
	public ZadanieRekrutacyjne(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "HeadMountedDisplay", "UMG", "Niagara", "GameplayTasks", "NavigationSystem" });
	}
}
