// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FRTSUtilitiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
