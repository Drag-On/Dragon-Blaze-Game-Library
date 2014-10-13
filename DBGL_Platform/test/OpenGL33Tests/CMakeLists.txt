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
project (DBGL_PLATFORM_TEST_OGL33 C CXX)

######################################################################
### Specify libraries that need copying
######################################################################
set(LIBRARIES2COPY
   "${DBGL_PLATFORM_LIB_DIR}/${DBGL_PLATFORM_DLL_NAME}"
   "${GLEW_LIB_DIR}/${GLEW_DLL_NAME}"
   "${GLFW_LIB_DIR}/${GLFW_DLL_NAME}"
)

######################################################################
### Add test cases
######################################################################
add_subdirectory("${PROJECT_SOURCE_DIR}/WindowTest"
				 "${PROJECT_BINARY_DIR}/WindowTest")
add_subdirectory("${PROJECT_SOURCE_DIR}/GraphicsTest"
				 "${PROJECT_BINARY_DIR}/GraphicsTest")
				 
######################################################################
### Copy common resource folder
######################################################################
#file(COPY "${PROJECT_SOURCE_DIR}/common" DESTINATION "${PROJECT_BINARY_DIR}")