// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class A_Fist_Full_Of_Pesos : ModuleRules
{
	public A_Fist_Full_Of_Pesos(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
