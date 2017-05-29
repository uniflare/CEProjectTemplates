#pragma once

#include <CryCore/CryTypeInfo.h>

namespace Modules
{
namespace Impl
{
struct IModuleImpl
{
	virtual ~IModuleImpl() {}

	//! Example module interface method
	virtual string GetString() = 0;
};
}
}

struct SModuleImplementations
{
	Modules::Impl::IModuleImpl* pExampleModule;
};