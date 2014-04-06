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
project (DBGL_BASE C CXX)

######################################################################
### Configure compilation details
######################################################################

#set (CMAKE_BUILD_TYPE Release)

set (DBGL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include") 			# Path to own headers
set (DBGL_LIB_DIR "${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}") 	# Path to own library file
set (GLEW_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/glew/lib/") 		# Path to GLEW library file
set (GLEW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/glew/include") # Path to GLEW headers
set (GLFW_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/glfw/src/") 		# Path to GLFW library file
set (GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/glfw/include") # Path to GLFW headers

set (DBGL_VERSION_MAJOR 0)
set (DBGL_VERSION_MINOR 1)
set (DBGL_VERSION_ADD 0)
set (DBGL_VERSION_FULL "${DBGL_VERSION_MAJOR}.${DBGL_VERSION_MINOR}.${DBGL_VERSION_ADD}")

######################################################################
### Platform specific stuff
######################################################################
if(WIN32)
	set (DBGL_DLL_NAME "libDBGL_Base.dll")
	set (GLEW_LIB_NAME "libglew32.dll.a")
	set (GLEW_DLL_NAME "glew32.dll")
	set (GLFW_LIB_NAME "glfw3dll.a")
	set (GLFW_DLL_NAME "glfw3.dll")
elseif(UNIX)
	set (DBGL_DLL_NAME "libDBGL_Base.so")
	set (GLEW_LIB_NAME "libGLEW.so")
	set (GLEW_DLL_NAME "libGLEW.so")
	set (GLFW_LIB_NAME "libglfw.so")
	set (GLFW_DLL_NAME "libglfw.so")
endif()
 
######################################################################
### Make header file
######################################################################
configure_file (
	"${DBGL_INCLUDE_DIR}/DBGL_Base_Config.h.in"
	"${DBGL_INCLUDE_DIR}/DBGL_Base_Config.h"
)

######################################################################
### Compiler flags
######################################################################
# GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11") # C++11
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")
endif(CMAKE_COMPILER_IS_GNUCXX)
# TODO: Other compilers
 
######################################################################
### Project code files
######################################################################
file(GLOB_RECURSE BASE_SRC
    "include/*.h"
    "src/*.cpp"
)

######################################################################
### Add target for doxygen
######################################################################
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
		${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile @ONLY
	)
	add_custom_target(doc
		${DOXYGEN_EXECUTABLE}
		${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating documentation..." VERBATIM
	)
else (DOXYGEN_FOUND)
	message("Doxygen not found!")
endif(DOXYGEN_FOUND)

######################################################################
### Include directories
######################################################################
include_directories(${DBGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

######################################################################
### Find OpenGL
######################################################################
find_package(OpenGL)
if (OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
	message("OpenGL environment missing!")
endif (OPENGL_FOUND)

######################################################################
### Make target
######################################################################
add_library(DBGL_Base SHARED ${BASE_SRC})
set_target_properties(DBGL_Base PROPERTIES LINKER_LANGUAGE CXX)

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_Base "${GLEW_LIB_DIR}/${GLEW_LIB_NAME}")
target_link_libraries(DBGL_Base "${GLFW_LIB_DIR}/${GLFW_LIB_NAME}")
target_link_libraries(DBGL_Base "${OPENGL_LIBRARIES}")

######################################################################
### Compile sub projects
######################################################################
add_subdirectory("${PROJECT_SOURCE_DIR}/Examples/"
				 "${PROJECT_BINARY_DIR}/Examples/")
