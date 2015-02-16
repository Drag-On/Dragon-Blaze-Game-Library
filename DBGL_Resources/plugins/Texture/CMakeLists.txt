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
### Examples cmake compilation file
######################################################################
cmake_minimum_required (VERSION 2.6)
project (DBGL_RESOURCES_PLUGINS_TEXTURE C CXX)

######################################################################
### Add plugin projects
######################################################################
add_subdirectory("${PROJECT_SOURCE_DIR}/BMP"
                 "${PROJECT_BINARY_DIR}/BMP")
add_subdirectory("${PROJECT_SOURCE_DIR}/TGA"
                 "${PROJECT_BINARY_DIR}/TGA")
add_subdirectory("${PROJECT_SOURCE_DIR}/DDS"
                 "${PROJECT_BINARY_DIR}/DDS")
