######################################################################
### Dragon Blaze Game Library
###
### Copyright (c) 2015 by Jan Moeller
###
### This software is provided "as-is" and does not claim to be
### complete or free of bugs in any way. It should work, but
### it might also begin to hurt your kittens.
######################################################################

######################################################################
### Project code files
######################################################################
file(GLOB_RECURSE SRC_FILES
    "DBGL_Resources/test/*.cpp"
)

######################################################################
### Include directories
######################################################################
include_directories(${DBGL_RESOURCES_INCLUDE_DIR})
include_directories(${DBGL_CORE_INCLUDE_DIR})
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_executable(DBGL_RESOURCES_TEST ${SRC_FILES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_RESOURCES_TEST DBGL_Resources)
target_link_libraries(DBGL_RESOURCES_TEST DBGL_Core)
target_link_libraries(DBGL_RESOURCES_TEST DBGL_Platform)
