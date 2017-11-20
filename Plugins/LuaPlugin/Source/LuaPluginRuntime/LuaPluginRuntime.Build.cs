// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LuaPluginRuntime : ModuleRules
{
	protected string ThirdPartyPath {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty")); }
    }

	public LuaPluginRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateIncludePaths.Add("LuaPluginRuntime/Private");

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
			}
			)

		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Lua", "Include"));

		if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "Lua", "Lib", "Win64", "Release", "lua.lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "Lua", "Lib", "Mac", "Release", "lua.a"));
        }
        else if(Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "Lua", "Lib", "Android", "Release", "lua.a"));
        }
        else if(Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "Lua", "Lib", "Ios", "Release", "lua.a"));
        }
	}
}
