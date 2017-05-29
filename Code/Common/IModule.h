#pragma once

#include <CrySystem/ICryPlugin.h>

struct IModuleSystem;
struct SModuleImplementations;

//! Interface to the Module Plugin
struct IModulePlugin
	: public ICryPlugin
{
	CRYINTERFACE_DECLARE(IModulePlugin, 0xC97AD475FAA5416D, 0x9C304AA2D2C5B7F6);

public:
	virtual IModuleSystem*				GetModuleSystem() const = 0;
	static IModulePlugin*				GetInstance() { return m_pThis; }
	virtual SModuleImplementations*		GetModules() = 0;

protected:
	static IModulePlugin* m_pThis;
};
DECLARE_SHARED_POINTERS(IModulePlugin);


//! Interface to the Public Module System
struct IModuleSystem
{
	virtual ~IModuleSystem() {}

	//! Test interface
	virtual void ModuleTest() = 0;
};