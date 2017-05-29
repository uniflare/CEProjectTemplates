#include "StdAfx.h"
#include "ModuleImpl.h"

// Fix to get gEnv in VS intellisense
#include <CryString/CryPath.h>

using namespace Modules::Impl;
using namespace Modules::Impl::ExampleModule;

CModuleImpl::CModuleImpl()
{
	CryLogAlways("CModuleImpl(ExampleModule) ctor");
}


string CModuleImpl::GetString() 
{
	return "Test String from Example Module.";
}