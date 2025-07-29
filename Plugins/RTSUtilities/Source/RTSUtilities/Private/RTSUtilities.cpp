// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSUtilities.h"

#define LOCTEXT_NAMESPACE "FRTSUtilitiesModule"

void FRTSUtilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FRTSUtilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRTSUtilitiesModule, RTSUtilities)