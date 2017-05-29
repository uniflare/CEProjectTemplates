#include "StdAfx.h"

// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>
#include <platform.inl>

#include "CryModuleSystem.h"
#include "ModuleSystem.h"


USE_CRYPLUGIN_FLOWNODES

IEntityRegistrator* IEntityRegistrator::g_pFirst = nullptr;
IEntityRegistrator* IEntityRegistrator::g_pLast = nullptr;
IModulePlugin* IModulePlugin::m_pThis = 0;

///////////////////////////////////////////////////////////////////////////
CPlugin_ModuleExample::CPlugin_ModuleExample()
	: m_pSystem(nullptr)
{

	if (!gEnvModules)
		gEnvModules = GetModules();

	m_pThis = this;
}

///////////////////////////////////////////////////////////////////////////
CPlugin_ModuleExample::~CPlugin_ModuleExample()
{
	gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);
	
	SAFE_DELETE(m_pSystem);

	IEntityRegistrator* pTemp = IEntityRegistrator::g_pFirst;
	while (pTemp != nullptr)
	{
		pTemp->Unregister();
		pTemp = pTemp->m_pNext;
	}
}

///////////////////////////////////////////////////////////////////////////
bool CPlugin_ModuleExample::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	// OPTIONAL MODULE EXAMPLE
	if (!gEnv->pSystem->InitializeEngineModule("ExampleModule", "EngineModule_ModuleExample", false))
		CryLogAlways("Warning: Unable to load example module. This feature will not be available.");
	else 
		if (!gEnvModules->pExampleModule)
		{
			CryLogAlways("Error: Module loaded but not available. Unloading module.");
			gEnv->pSystem->UnloadEngineModule("ExampleModule", "EngineModule_ModuleExample");
		}
		else
		{
			CryLogAlways("Loaded ExampleModule Implementation. String: %s", gEnvModules->pExampleModule->GetString());
		}

	m_pSystem = new CModuleSystem();
	
	env.pSystem->GetISystemEventDispatcher()->RegisterListener(this);

	return (m_pSystem != nullptr);
}

///////////////////////////////////////////////////////////////////////////
void CPlugin_ModuleExample::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	switch (event)
	{

	case ESYSTEM_EVENT_GAME_POST_INIT:
	{
		// Register entities
		IEntityRegistrator* pTemp = IEntityRegistrator::g_pFirst;
		while (pTemp != nullptr)
		{
			pTemp->Register();
			pTemp = pTemp->m_pNext;
		}
	}
	break;
	}

	if (m_pSystem)
		m_pSystem->OnSystemEvent(event, wparam, lparam);
}

///////////////////////////////////////////////////////////////////////////
IModuleSystem* CPlugin_ModuleExample::GetModuleSystem() const
{
	return m_pSystem;
}

///////////////////////////////////////////////////////////////////////////
SModuleImplementations * CPlugin_ModuleExample::GetModules()
{
	return &m_pModules;
}

CRYREGISTER_SINGLETON_CLASS(CPlugin_ModuleExample)

#include <CryCore/CrtDebugStats.h>