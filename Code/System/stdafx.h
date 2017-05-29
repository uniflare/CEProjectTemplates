#pragma once

#include <CryCore/Project/CryModuleDefs.h>
#define eCryModule eCryM_EnginePlugin
#define GAME_API   DLL_EXPORT

#include <CryCore/Platform/platform.h>

#if !defined(_RELEASE)
#define ENABLE_VIDEO_LOGGING
#endif // _RELEASE

#include <CryCore/Project/ProjectDefines.h>

//#include <CryCore/StlUtils.h>
//#include "VideoAllocator.h"
//extern CVideoAllocator<13 * 1024 * 1024> g_videoMemoryPoolPrimary;
//extern CVideoLogger g_videoLogger;
//extern CTimeValue g_lastMainThreadFrameStartTime;
//#define VIDEO_ALLOCATOR_MEMORY_POOL g_videoMemoryPoolPrimary
//#include <STLVideoAllocator.h>

