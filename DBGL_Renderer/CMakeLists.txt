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
file(GLOB_RECURSE SRC
    "DBGL_Renderer/src/*.cpp"
)

######################################################################
### Include directories
######################################################################
include_directories(${DBGL_RENDERER_INCLUDE_DIR})
include_directories(${DBGL_RESOURCES_INCLUDE_DIR})
include_directories(${DBGL_CORE_INCLUDE_DIR})
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_library(DBGL_Renderer SHARED ${SRC})
set_target_properties(DBGL_Renderer PROPERTIES LINKER_LANGUAGE CXX)

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_Renderer DBGL_Platform)
target_link_libraries(DBGL_Renderer DBGL_Core)
target_link_libraries(DBGL_Renderer DBGL_Resources)

######################################################################
### Compile tests
######################################################################
#include()

######################################################################
### Compile examples
######################################################################
include("DBGL_Renderer/examples/Simple/CMakeLists.txt")