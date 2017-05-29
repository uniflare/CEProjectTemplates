# Project: CMakePluginWithModule
# Brief: Top level CMakeLists
# Project Type: Dynamic DLL
# 
# Includes Common interfaces for Custom Modules.
# Also includes an example module (in this example, it is optional, a null impl can be used instead)
# The system mirrors the CryAudioSystem module setup but as a plugin
# This is a bare bones example demonstrating the modular framework available by using EngineModules.

cmake_minimum_required (VERSION 3.6.0)

# This allows us to next projects inside solution folders in our top-level solution file.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Load Common interface CMakeLists
add_subdirectory("Common")

# Load ExampleModule CMakeLists
add_subdirectory("modules/ExampleModule")

# ///////////////////////////////////////////////////////////
## TOP-LEVEL PROJECT ##

# Standard CMakeLists setup for a plugin project...

# Top-Level CMake project. (This string defines the output name - dll name)
project ("CMakePluginWithModule" VERSION 1.0 LANGUAGES CXX)

# Copy the vcxproj.user.in file to the generated project folder
if (${CMAKE_GENERATOR} MATCHES "^Visual Studio")
	# Set startup project properties
	configure_file ("${PROJECT_NAME}.vcxproj.user.in" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user")
	
	# Set the VS Debugger default startup project to the current project
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

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
	"ModuleSystem.cpp"
	"CryModuleSystem.cpp"
)
source_group("Source Files" FILES ${SourceGroup_Source})

set (SourceGroup_Header
	"ModuleImpl.h"
	"ModuleSystem.h"
	"CryModuleSystem.h"
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
  "Common"
)

target_link_libraries(${PROJECT_NAME} PRIVATE CryCommon CryAction)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE Ntdll)
endif(WIN32)

## ~TOP-LEVEL PROJECT ##
# ///////////////////////////////////////////////////////////