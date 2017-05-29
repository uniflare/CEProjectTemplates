#pragma once

#include <IGameObjectSystem.h>
#include <CrySystem\ISystem.h>
#include <IModule.h>
#include <IModuleImpl.h>

#define MAX_MODULE_NAME_LENGTH 256

class CModuleSystem;
class CPlugin_ModuleExample : public IModulePlugin
	, public ISystemEventListener
{
	CRYINTERFACE_BEGIN()
		CRYINTERFACE_ADD(IModulePlugin)
		CRYINTERFACE_ADD(ICryPlugin)
		CRYINTERFACE_END()

		CRYGENERATE_SINGLETONCLASS(CPlugin_ModuleExample, "Plugin_ModuleExample", 0x470ABC8C03A34438, 0x9777BE26B1F11593)

		CPlugin_ModuleExample();
		virtual ~CPlugin_ModuleExample();

		//! Retrieve name of plugin.
		virtual const char* GetName() const override { return "ModuleExamplePlugin"; }

		//! Retrieve category for the plugin.
		virtual const char* GetCategory() const override { return "Plugin"; }

		//! This is called to initialize the new plugin.
		virtual bool Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;
public:
	virtual IModuleSystem* GetModuleSystem() const override;
	virtual SModuleImplementations* GetModules() override;

	// ISystemEventListener
	virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
	// ~ISystemEventListener

protected:
	virtual void OnPluginUpdate(EPluginUpdateType updateType) override {}

private:
	CModuleSystem* m_pSystem;
	SModuleImplementations m_pModules;

public:
	template<class T>
	struct CObjectCreator : public IGameObjectExtensionCreatorBase
	{
		IGameObjectExtension* Create(IEntity* pEntity)
		{
			return pEntity->CreateComponentClass<T>();
		}

		void GetGameObjectExtensionRMIData(void** ppRMI, size_t* nCount)
		{
			*ppRMI = nullptr;
			*nCount = 0;
		}
	};

	template<class T>
	static void RegisterEntityWithDefaultComponent(const char *name)
	{
		IEntityClassRegistry::SEntityClassDesc clsDesc;
		clsDesc.sName = name;

		static CObjectCreator<T> _creator;

		gEnv->pGameFramework->GetIGameObjectSystem()->RegisterExtension(name, &_creator, &clsDesc);
	}

	template<class T>
	static void RegisterEntityComponent(const char *name)
	{
		static CObjectCreator<T> _creator;

		gEnv->pGameFramework->GetIGameObjectSystem()->RegisterExtension(name, &_creator, nullptr);
		T::SetExtensionId(gEnv->pGameFramework->GetIGameObjectSystem()->GetID(name));
	}
};

struct IEntityRegistrator
{
	IEntityRegistrator()
	{
		if (g_pFirst == nullptr)
		{
			g_pFirst = this;
			g_pLast = this;
		}
		else
		{
			g_pLast->m_pNext = this;
			g_pLast = g_pLast->m_pNext;
		}
	}

	virtual void Register() = 0;
	virtual void Unregister() = 0;

public:
	IEntityRegistrator *m_pNext;

	static IEntityRegistrator *g_pFirst;
	static IEntityRegistrator *g_pLast;
};