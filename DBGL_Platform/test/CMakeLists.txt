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
### Main library cmake compilation file
######################################################################
cmake_minimum_required (VERSION 2.6)
project (DBGL_PLATFORM_TEST C CXX)

add_subdirectory("${PROJECT_SOURCE_DIR}/OpenGL33Tests/"
				 "${PROJECT_BINARY_DIR}/OpenGL33Tests/")