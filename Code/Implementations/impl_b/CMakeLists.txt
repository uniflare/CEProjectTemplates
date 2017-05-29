# Project: Example Implementation B
# Brief: An example implementation of the example implementation interface :)
# Project Type: Plugin, Sub-Module
# 

# This string defines the output name - dll name - for this project
project ("ExampleImpl_B" VERSION 1.0 LANGUAGES CXX)
	

# Required Packages
find_package (CryCommon REQUIRED)

# Source files
set (SourceGroup_NoUber
	"stdafx.cpp"
	"stdafx.h"
)
source_group("" FILES ${SourceGroup_NoUber})

set (SourceGroup_Source
	"CryPlugin.cpp"
	"ExampleImpl.cpp"
)
source_group("Source Files" FILES ${SourceGroup_Source})

set (SourceGroup_Header
	"CryPlugin.h"
	"ExampleImpl.h"
)
source_group("Header Files" FILES ${SourceGroup_Header})

set (SOURCE
	${SourceGroup_Source}
	${SourceGroup_Header}
	${SourceGroup_NoUber}
)

if(OPTION_PCH AND MSVC)
	set (PRECOMPILED_SOURCE ${SOURCE})
	list(REMOVE_ITEM PRECOMPILED_SOURCE "stdafx.cpp")

	set (PRECOMPILED_BINARY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pch)
	set_source_files_properties (${PRECOMPILED_SOURCE} PROPERTIES COMPILE_FLAGS "/Yu\"stdafx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_DEPENDS "${PRECOMPILED_BINARY}")
	set_source_files_properties (stdafx.cpp PROPERTIES COMPILE_FLAGS "/Yc\"stdafx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_OUTPUTS "${PRECOMPILED_BINARY}")
endif (OPTION_PCH AND MSVC)

add_library(${PROJECT_NAME} MODULE ${SOURCE})

#BEGIN-CUSTOM
# Preparation patch for 5.4
if(CE_CMAKE_NEW)
	set(T_CRYENGINE_DIR ${CRYENGINE_DIR})
	set(T_PROJECT_NAME ${THIS_PROJECT})
else()
	set(T_CRYENGINE_DIR ${CryEngine_DIR})
	set(T_PROJECT_NAME ${PROJECT_NAME})
endif()

# Include common and required ffmpeg headers
target_include_directories(${T_PROJECT_NAME} PRIVATE 
	"${CMAKE_SOURCE_DIR}/Common" 
	"${OPTION_SDK_DIRECTORY}/${OPTION_EXAMPLE_SDK_DIRECTORY}/include"
)

# Include required FFMpeg libraries
link_directories("${OPTION_SDK_DIRECTORY}/${OPTION_EXAMPLE_SDK_DIRECTORY}/lib")

# Nest this project in a solution folder in VS
set_property(TARGET ${T_PROJECT_NAME} PROPERTY FOLDER "MultiPluginExample/Implementations")

# Set a custom output file name for this project
set_target_properties(
    ${T_PROJECT_NAME} 
    PROPERTIES 
		OUTPUT_NAME "ExampleImpl_B"
#		SUFFIX ".dll"
)

# Add a Post-Build step to copy the ffmpeg binaries to the used engine dir
add_custom_command(TARGET ${T_PROJECT_NAME} POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy "${OPTION_SDK_DIRECTORY}/${OPTION_EXAMPLE_SDK_DIRECTORY}/bin/win_x64/ThirdPartyLib.dll" "${T_CRYENGINE_DIR}/bin/win_x64/"
)
#END-CUSTOM

target_link_libraries(${PROJECT_NAME} PRIVATE CryCommon)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE Ntdll)
endif(WIN32)