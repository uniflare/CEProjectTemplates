#include "StdAfx.h"
#include "ModuleSystem.h"
#include <Cry3DEngine/I3DEngine.h>


///////////////////////////////////////////////////////////////////////////
CModuleSystem::CModuleSystem()
{

	gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this);
}

///////////////////////////////////////////////////////////////////////////
CModuleSystem::~CModuleSystem()
{
	gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);
}

///////////////////////////////////////////////////////////////////////////
void CModuleSystem::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	gEnv->pConsole->PrintLine("CVideoSystem::OnSystemEvent");
	switch (event)
	{
	case ESYSTEM_EVENT_GAME_FRAMEWORK_INIT_DONE:
	{
		
		break;
	}
	case ESYSTEM_EVENT_FAST_SHUTDOWN:
	case ESYSTEM_EVENT_FULL_SHUTDOWN:
	default:
	{
		break;
	}
	}
}

///////////////////////////////////////////////////////////////////////////
void CModuleSystem::ModuleTest()
{
	gEnv->pConsole->PrintLine("ModuleTest Success");
}
