#include "stdafx.h"
#include "CryPlugin.h"

// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>

CExamplePlugin::~CExamplePlugin()
{
}

bool CExamplePlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	gEnv->pLog->LogAlways("MultiPluginExample::CExamplePlugin::Initialize()");
	return true;
}

CRYREGISTER_SINGLETON_CLASS(CExamplePlugin)