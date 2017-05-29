#include "stdafx.h"
#include "CryPlugin.h"

// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>

CExampleImplPlugin::~CExampleImplPlugin()
{
}

bool CExampleImplPlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	gEnv->pLog->LogAlways("ExampleImpl_A::CExamplePlugin::Initialize()");
	return true;
}

CRYREGISTER_SINGLETON_CLASS(CExampleImplPlugin)
