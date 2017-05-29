# Define source files and source groups
set (SourceGroup_NoUber
	"IModule.h"
	"IModuleImpl.h"
	"platform.inl"
)
source_group("" FILES ${SourceGroup_NoUber})

set (SOURCE
	${SourceGroup_NoUber}
)

# We require CryCommon. You could add cryaction too, but would need to modify the props file accordingly.
find_package (CryCommon REQUIRED)

# Project
project("ModuleCommon" VERSION 1.0 LANGUAGES CXX)

# Only for VS
if (${CMAKE_GENERATOR} MATCHES "^Visual Studio")
	# Load our props file
	configure_file ("${PROJECT_NAME}.vcxproj.user.in" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user")
endif()

# This is a workaround for CMAKE to add interface files to the project
set (THIS_PROJECT ${PROJECT_NAME} PARENT_SCOPE)
set (THIS_PROJECT ${PROJECT_NAME})
add_custom_target( ${THIS_PROJECT} SOURCES ${SOURCE})

# Nest this project in a solution folder in VS
set_property(TARGET ${THIS_PROJECT} PROPERTY FOLDER "Common")