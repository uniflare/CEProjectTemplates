#pragma once

#include <CrySystem/ISystem.h>
#include <CryGame/IGameFramework.h>
#include <IModule.h>
#include <IModuleImpl.h>

class CModuleSystem
	: public IModuleSystem
	, public ISystemEventListener
{

protected:

public:
	CModuleSystem();
	~CModuleSystem();

	virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;

	
	virtual void ModuleTest() override;
};