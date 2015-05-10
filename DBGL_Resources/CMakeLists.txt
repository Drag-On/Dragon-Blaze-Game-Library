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
    "DBGL_Resources/src/*.cpp"
    "DBGL_Resources/src/*.h"
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
add_library(DBGL_Resources SHARED ${SRC})
set_target_properties(DBGL_Resources PROPERTIES LINKER_LANGUAGE CXX)

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_Resources DBGL_Platform)
target_link_libraries(DBGL_Resources DBGL_Core)

######################################################################
### Compile plugins
######################################################################
include("${PROJECT_SOURCE_DIR}/DBGL_Resources/plugins/Mesh/OBJ/CMakeLists.txt")
include("${PROJECT_SOURCE_DIR}/DBGL_Resources/plugins/Texture/BMP/CMakeLists.txt")
include("${PROJECT_SOURCE_DIR}/DBGL_Resources/plugins/Texture/DDS/CMakeLists.txt")
include("${PROJECT_SOURCE_DIR}/DBGL_Resources/plugins/Texture/TGA/CMakeLists.txt")

######################################################################
### Compile tests
######################################################################
include("${PROJECT_SOURCE_DIR}/DBGL_Resources/test/CMakeLists.txt")

######################################################################
### Compile examples
######################################################################
include("${PROJECT_SOURCE_DIR}/DBGL_Resources/examples/ModelViewer/CMakeLists.txt")