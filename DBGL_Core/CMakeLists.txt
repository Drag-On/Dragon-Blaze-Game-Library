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
### Main library cmake compilation file
######################################################################
cmake_minimum_required (VERSION 2.6)
project (DBGL_CORE C CXX)
 
######################################################################
### Project code files
######################################################################
file(GLOB_RECURSE SRC
    "include/*.h"
    "src/*.cpp"
)

######################################################################
### Include directories
######################################################################
include_directories(${DBGL_CORE_INCLUDE_DIR})
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_library(DBGL_Core SHARED ${SRC})
set_target_properties(DBGL_Core PROPERTIES LINKER_LANGUAGE CXX)

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_Core "${DBGL_LIB_DIR}/${DBGL_PLATFORM_LIB_NAME}")
