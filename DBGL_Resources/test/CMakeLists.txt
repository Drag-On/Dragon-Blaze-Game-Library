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
project (DBGL_RESOURCES_TEST C CXX)

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
add_executable(DBGL_RESOURCES_TEST ${SRC_FILES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_RESOURCES_TEST "${DBGL_LIB_DIR}/${DBGL_RESOURCES_DLL_NAME}")
target_link_libraries(DBGL_RESOURCES_TEST "${DBGL_LIB_DIR}/${DBGL_CORE_DLL_NAME}")
target_link_libraries(DBGL_RESOURCES_TEST "${DBGL_LIB_DIR}/${DBGL_PLATFORM_DLL_NAME}")

######################################################################
### Specify files that need to be copied
######################################################################
set(Files2Copy
   "MeshTests/test.obj"
   "TextureTests/test.bmp"
   "TextureTests/test.DDS"
   "TextureTests/test.tga"
)

######################################################################
### Copy files
######################################################################
add_custom_target(ALWAYS_EXECUTE_RESOURCES_TESTS ALL)
add_dependencies(DBGL_RESOURCES_TEST ALWAYS_EXECUTE_RESOURCES_TESTS)
# do the copying
foreach(file_i ${Files2Copy})
	add_custom_command(TARGET ALWAYS_EXECUTE_RESOURCES_TESTS
                        PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/${file_i}" "${PROJECT_BINARY_DIR}/${file_i}"
                        DEPENDS "${PROJECT_SOURCE_DIR}/${file_i}"
                        )
endforeach(file_i)