# Project: Multi Plugin Example
# Brief: Multi-Plugin Example with implementation/import examples
# Project Type: Various
# 
# Note this cmakelist is just a wrapper for all projects residing in this system.
# 

cmake_minimum_required (VERSION 3.6.0)

# This string defines the solution name - dll name - for this project
project ("MultiPluginExample" VERSION 1.0 LANGUAGES CXX)

# This allows us to nest projects inside solution folders in our top-level solution file.
option(OPTION_PCH "Enable Precompiled headers" ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#BEGIN-CUSTOM
# 5.3->5.4 Compatibility
set(T_PROJECT_NAME ${PROJECT_NAME})
if("${CryEngine_DIR}" STREQUAL "")
	set(CE_CMAKE_NEW 1)
	set(T_PROJECT_NAME ${THIS_PROJECT})
	message(WARNING "NEW CMAKE LAYOUT DETECTED: ${CryEngine_DIR}")
else()
	set(CE_CMAKE_NEW 0)
	message(WARNING "OLD CMAKE LAYOUT DETECTED: ${CryEngine_DIR}")
endif()

# Disable building FFMpeg decoder if no SDK
set (OPTION_SDK_DIRECTORY "${CMAKE_SOURCE_DIR}/SDKs" CACHE STRING "Location of all SDK sub folders used in this project.")
set (OPTION_EXAMPLE_SDK_DIRECTORY "ExampleSDK" CACHE STRING "Location of the example SDK includes, libraries and binaries.")
set (OPTION_EXAMPLE_IMPL_B_ENABLE ON CACHE BOOL "Build Example Implemenation B using Example SDK.")
if (NOT EXISTS "${OPTION_SDK_DIRECTORY}/${OPTION_EXAMPLE_SDK_DIRECTORY}")
	set (OPTION_EXAMPLE_IMPL_B_ENABLE OFF FORCE)
	message(WARNING "Example SDK not found. This feature will be unavailable.")
endif ()

# Put lib exports to output bin/libs folder for all projects
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO 	${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL 		${CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 			${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO 	${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 					${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libs)

# If this project is ever shown, it should not be in the visible build structure.
if(TARGET ${T_PROJECT_NAME})
	set_property(TARGET ${T_PROJECT_NAME} PROPERTY FOLDER "CMakePredefinedTargets")
endif()

# Load project system
add_subdirectory("Common")
add_subdirectory("System")
add_subdirectory("Implementations")
add_subdirectory("SDKs")
#END-CUSTOM