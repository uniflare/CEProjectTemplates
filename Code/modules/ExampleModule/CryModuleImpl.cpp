#include "StdAfx.h"
#include "ModuleImpl.h"
#include <CryCore/Platform/platform_impl.inl>
#include <platform.inl>
#include <CrySystem/IEngineModule.h>
#include <CryExtension/ClassWeaver.h>
#include <CryExtension/ICryPluginManager.h>
#include <IModule.h>


using namespace Modules::Impl::ExampleModule;

//////////////////////////////////////////////////////////////////////////
class CEngineModule_ModuleExample : public IEngineModule
{

	CRYINTERFACE_SIMPLE(IEngineModule)
		CRYGENERATE_SINGLETONCLASS(CEngineModule_ModuleExample, "EngineModule_ModuleExample", 0x8030c0d1901b4031, 0xa3785a7b53125f3f)

	CEngineModule_ModuleExample() {};
	virtual ~CEngineModule_ModuleExample() {}

	//////////////////////////////////////////////////////////////////////////
	virtual char const* GetName()     override { return "ModuleExample"; }
	virtual char const* GetCategory() override { return "Module"; }

	//////////////////////////////////////////////////////////////////////////
	virtual bool Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override
	{
		// Usually would use some abstract system to pass this pointer (shared ptr) 
		// to the proper component in our system (Modulesystem)

		// For now we use our own defined global variable for custom modules
		auto pModule = new CModuleImpl();

		ICryPluginManager* pPluginManager = GetISystem()->GetIPluginManager();
		if (pPluginManager != nullptr)
		{
			// reference
			auto InterfaceID = cryiidof<IModulePlugin>();

			// INTERFACE TEST
			auto pModulePlugin = pPluginManager->QueryPlugin<IModulePlugin>();
			if (pModulePlugin != nullptr)
			{
				if (!gEnvModules)
					gEnvModules = pModulePlugin->GetModules();
				gEnvModules->pExampleModule = pModule;
				return true;
			}

			/*
			// EXTENSION TEST (Requires RegisterExtension!)
			auto pInterface = gEnv->pGameFramework->QueryExtension<IModulePlugin>();
			if (pInterface != nullptr)
			{
				if (!gEnvModules)
					gEnvModules = pInterface->GetModules();
				gEnvModules->pExampleModule = pModule;
				return true;
			}

			// PLUGIN TEST (Fallback)
			CPlugin_ModuleExample* pPlugin = pPluginManager->QueryPlugin<CPlugin_ModuleExample>();
			if (pPlugin != nullptr)
			{
				if (!gEnvModules)
					gEnvModules = pPlugin->GetModules();
				gEnvModules->pExampleModule = pModule;
				return true;
			}
			*/
		}


		return true;
	}
};
CRYREGISTER_SINGLETON_CLASS(CEngineModule_ModuleExample)

#include <CryCore/CrtDebugStats.h>