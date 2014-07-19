######################################################################
### Dragon Blaze Game Library
###
### Copyright (c) 2014 by Jan Moeller
###
### This software is provided "as-is" and does not claim to be
### complete or free of bugs in any way. It should work, but
### it might also begin to hurt your kittens.
######################################################################

######################################################################
### Movement example cmake compilation file
######################################################################
cmake_minimum_required (VERSION 2.6)
project (DBGL_BASE_ENTITIES C CXX)

######################################################################
### Project code files
######################################################################
file(GLOB_RECURSE SRC_FILES_ENTITIES
    "*.h"
    "*.cpp"
)

######################################################################
### Include directories
######################################################################
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${DBGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_executable(DBGL_BASE_ENTITIES ${SRC_FILES_ENTITIES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_BASE_ENTITIES "${PROJECT_BINARY_DIR}/${DBGL_DLL_NAME}")

######################################################################
### Copy files
######################################################################
set(LIBRARIES2COPY
   "${DBGL_LIB_DIR}/${DBGL_DLL_NAME}"
   "${GLEW_LIB_DIR}/${GLEW_DLL_NAME}"
   "${GLFW_LIB_DIR}/${GLFW_DLL_NAME}"
)
add_custom_target(ALWAYS_EXECUTE_ENTITIES ALL)
add_dependencies(DBGL_BASE_ENTITIES ALWAYS_EXECUTE_ENTITIES)
# do the copying
foreach(file_i ${LIBRARIES2COPY})
	add_custom_command(TARGET ALWAYS_EXECUTE_ENTITIES
                        PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file_i} "${PROJECT_BINARY_DIR}"
                        DEPENDS ${file_i}
                        )
endforeach(file_i)