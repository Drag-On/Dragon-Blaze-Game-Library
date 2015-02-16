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
### Basics example cmake compilation file
######################################################################
cmake_minimum_required (VERSION 2.6)
project (DBGL_PLATFORM_TEST_OS_MODULE C CXX)

######################################################################
### Project code files
######################################################################
file(GLOB_RECURSE SRC_FILES
    "*.h"
    "*.cpp"
)

######################################################################
### Include directories
######################################################################
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_executable(DBGL_PLATFORM_TEST_OS_MODULE ${SRC_FILES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_PLATFORM_TEST_OS_MODULE "${DBGL_LIB_DIR}/${DBGL_PLATFORM_DLL_NAME}")
