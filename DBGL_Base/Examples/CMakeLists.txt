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
### Examples cmake compilation file
######################################################################
cmake_minimum_required (VERSION 2.6)
project (DBGL_BASE_EXAMPLES C CXX)

# External examples
add_subdirectory("${PROJECT_SOURCE_DIR}/Basics"
				 "${PROJECT_SOURCE_DIR}/Basics")
add_subdirectory("${PROJECT_SOURCE_DIR}/Movement"
				 "${PROJECT_SOURCE_DIR}/Movement")
add_subdirectory("${PROJECT_SOURCE_DIR}/Shader"
				 "${PROJECT_SOURCE_DIR}/Shader")