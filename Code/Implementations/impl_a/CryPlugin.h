#pragma once

#include <CrySystem/ICryPlugin.h>
#include <CryEntitySystem/IEntityClass.h>

class CExampleImplPlugin
	: public ICryPlugin
{
public:
	CRYINTERFACE_SIMPLE(ICryPlugin)
		CRYGENERATE_SINGLETONCLASS(CExampleImplPlugin, "ExampleImpl_A", 0x7E577E577E577E57, 0x0000000000000002)
		virtual ~CExampleImplPlugin();

	//! Retrieve name of plugin.
	virtual const char*		GetName() const override { return "ExampleImpl_A"; }

	//! Retrieve category for the plugin.
	virtual const char*		GetCategory() const override { return "Plugin"; }
	virtual bool			Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;
	virtual void			OnPluginUpdate(EPluginUpdateType updateType) override {}
};