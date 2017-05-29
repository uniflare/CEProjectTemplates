# CMakeList: ExampleModule
# Brief: Example implementation project
# Project Type: Dynamic DLL
# 
# Includes Common interfaces for Custom Modules.
# Also includes an example module (in this example, it is optional, a null impl can be used instead)
# The system mirrors the CryAudioSystem module setup but as a plugin
# This is a bare bones example demonstrating the modular framework available by using EngineModules.

cmake_minimum_required (VERSION 3.6.0)
project ("ExampleModule" VERSION 1.0 LANGUAGES CXX)
option(OPTION_PCH "Enable Precompiled headers" ON)

# Required Packages
find_package (CryCommon REQUIRED)
find_package (CryAction REQUIRED)

# Source files
set (SourceGroup_NoUber
	"StdAfx.cpp"
	"StdAfx.h"
)
source_group("" FILES ${SourceGroup_NoUber})

set (SourceGroup_Source
	"ModuleImpl.cpp"
	"CryModuleImpl.cpp"
)
source_group("Source Files" FILES ${SourceGroup_Source})

set (SourceGroup_Header
	"ModuleImpl.h"
)
source_group("Header Files" FILES ${SourceGroup_Header})

set (SOURCE
	${SourceGroup_Source}
	${SourceGroup_Header}
	${SourceGroup_NoUber}
)

if(OPTION_PCH AND MSVC)
	set (PRECOMPILED_SOURCE ${SOURCE})
	list(REMOVE_ITEM PRECOMPILED_SOURCE "StdAfx.cpp")

	set (PRECOMPILED_BINARY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pch)
	set_source_files_properties (${PRECOMPILED_SOURCE} PROPERTIES COMPILE_FLAGS "/Yu\"StdAfx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_DEPENDS "${PRECOMPILED_BINARY}")
	set_source_files_properties (StdAfx.cpp PROPERTIES COMPILE_FLAGS "/Yc\"StdAfx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_OUTPUTS "${PRECOMPILED_BINARY}")
endif (OPTION_PCH AND MSVC)

add_library(${PROJECT_NAME} MODULE ${SOURCE})

# Add the common interfaces to our include directories
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  "../../Common"
)

# Nest this project inside a VS Solution folder
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "modules")

target_link_libraries(${PROJECT_NAME} PRIVATE CryCommon CryAction)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE Ntdll)
endif(WIN32)