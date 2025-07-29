// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RealTimeStrategyEditorTarget : TargetRules
{
	public RealTimeStrategyEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("RealTimeStrategy");
	}
}
