#pragma once

#include <CryCore/Project/CryModuleDefs.h>
#define eCryModule eCryM_EnginePlugin
#define GAME_API   DLL_EXPORT

#include <CryCore/Platform/platform.h>

#if !defined(_RELEASE)
#define ENABLE_VIDEO_LOGGING
#endif // _RELEASE

#include <CryCore/Project/ProjectDefines.h>