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
project (DBGL_TGA C CXX)

######################################################################
### Compiler flags
######################################################################
# GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
endif(CMAKE_COMPILER_IS_GNUCXX)

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
include_directories(${DBGL_RESOURCES_INCLUDE_DIR})
include_directories(${DBGL_CORE_INCLUDE_DIR})
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_library(DBGL_TGA SHARED ${SRC_FILES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_TGA "${DBGL_LIB_DIR}/${DBGL_PLATFORM_DLL_NAME}")
target_link_libraries(DBGL_TGA "${DBGL_LIB_DIR}/${DBGL_CORE_DLL_NAME}")
