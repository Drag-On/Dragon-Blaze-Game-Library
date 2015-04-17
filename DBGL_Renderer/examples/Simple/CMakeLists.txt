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
    "DBGL_Renderer/examples/Simple/*.cpp"
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
add_executable(DBGL_RENDERER_EXAMPLE_SIMPLE ${SRC_FILES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_RENDERER_EXAMPLE_SIMPLE DBGL_Renderer)
target_link_libraries(DBGL_RENDERER_EXAMPLE_SIMPLE DBGL_Resources)
target_link_libraries(DBGL_RENDERER_EXAMPLE_SIMPLE DBGL_Core)
target_link_libraries(DBGL_RENDERER_EXAMPLE_SIMPLE DBGL_Platform)
