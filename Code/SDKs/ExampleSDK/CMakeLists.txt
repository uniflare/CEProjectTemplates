#BEGIN-CUSTOM
#Preperation for 5.4
if("${THIS_PROJECT}" STREQUAL "ExampleSDK")
	# Nest this project inside a solution folder
	set_property(TARGET ${THIS_PROJECT} PROPERTY FOLDER "SDKs")
endif()
#END-CUSTOM