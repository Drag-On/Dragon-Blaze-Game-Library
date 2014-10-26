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
### Basics example cmake compilation file
######################################################################
cmake_minimum_required (VERSION 2.6)
project (DBGL_CORE_TEST_HASHING_OAT C CXX)

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
include_directories(${DBGL_CORE_INCLUDE_DIR})
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_executable(DBGL_CORE_TEST_HASHING_OAT ${SRC_FILES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_CORE_TEST_HASHING_OAT "${PROJECT_BINARY_DIR}/${DBGL_CORE_DLL_NAME}")
target_link_libraries(DBGL_CORE_TEST_HASHING_OAT "${PROJECT_BINARY_DIR}/${DBGL_PLATFORM_DLL_NAME}")

######################################################################
### Copy files
######################################################################
add_custom_target(ALWAYS_EXECUTE_HASHING_OAT ALL)
add_dependencies(DBGL_CORE_TEST_HASHING_OAT ALWAYS_EXECUTE_HASHING_OAT)
# do the copying
foreach(file_i ${LIBRARIES2COPY})
	add_custom_command(TARGET ALWAYS_EXECUTE_HASHING_OAT
                        PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file_i} "${PROJECT_BINARY_DIR}"
                        DEPENDS ${file_i}
                        )
endforeach(file_i)