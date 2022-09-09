// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LearnUE4 : ModuleRules
{
	public LearnUE4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Core Modules
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		// GAS Modules
		PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });

		// AI Modules
		PublicDependencyModuleNames.AddRange(new string[] { "NavigationSystem", "AIModule" });

		// Input
		PublicDependencyModuleNames.AddRange(new string[] { "EnhancedInput" });

		// UI Modules
		PublicDependencyModuleNames.AddRange(new string[] { "UMG" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Shader Modules
		PublicDependencyModuleNames.AddRange(new string[] { "RHI", "RenderCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}