#pragma once

#include <CrySystem/ICryPlugin.h>

#include <CryEntitySystem/IEntityClass.h>

class CExamplePlugin
	: public ICryPlugin
{
public:
	CRYINTERFACE_SIMPLE(ICryPlugin)
		CRYGENERATE_SINGLETONCLASS(CExamplePlugin, "Multi_Plugin_Example", 0x7E577E577E577E57, 0x0000000000000001)
		virtual ~CExamplePlugin();

	//! Retrieve name of plugin.
	virtual const char*		GetName() const override { return "MultiPluginExample"; }

	//! Retrieve category for the plugin.
	virtual const char*		GetCategory() const override { return "Plugin"; }
	virtual bool			Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;
	virtual void			OnPluginUpdate(EPluginUpdateType updateType) override {}
};