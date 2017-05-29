# Define source files and source groups
set (SourceGroup_NoUber
	"ICommonExample.h"
	"IExampleImpl.h"
)
source_group("" FILES ${SourceGroup_NoUber})

set (SOURCE
	${SourceGroup_NoUber}
)

# We require CryCommon. You could add cryaction too, but would need to modify the props file accordingly.
find_package (CryCommon REQUIRED)

# Project
project("Common" VERSION 1.0 LANGUAGES CXX)

# This is a workaround for CMAKE to add interface files to the project
set (THIS_PROJECT ${PROJECT_NAME} PARENT_SCOPE)
set (THIS_PROJECT ${PROJECT_NAME})
add_custom_target( ${THIS_PROJECT} SOURCES ${SOURCE})

#BEGIN-CUSTOM
# Preparation patch for 5.4
if(CE_CMAKE_NEW)
	set(T_PROJECT_NAME ${THIS_PROJECT})
else()
	set(T_PROJECT_NAME ${PROJECT_NAME})
endif()

# Only for VS
if (${CMAKE_GENERATOR} MATCHES "^Visual Studio")
	# Fix to add CryCommon include directories to this non-library project
	configure_file ("CryCommon.vcxproj.user.in" "${CMAKE_CURRENT_BINARY_DIR}/${T_PROJECT_NAME}.vcxproj.user")
	configure_file ("CryCommon.props" "${CMAKE_CURRENT_BINARY_DIR}/CryCommon.props")
endif()

# Nest this project inside a solution folder
set_property(TARGET ${T_PROJECT_NAME} PROPERTY FOLDER "MultiPluginExample/Common")
#END-CUSTOM