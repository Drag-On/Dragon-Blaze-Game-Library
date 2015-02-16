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
project (DBGL_RESOURCES_PLUGINS C CXX)

add_subdirectory("${PROJECT_SOURCE_DIR}/Texture/"
                 "${PROJECT_BINARY_DIR}/Texture/")
add_subdirectory("${PROJECT_SOURCE_DIR}/Mesh/"
                 "${PROJECT_BINARY_DIR}/Mesh/")
