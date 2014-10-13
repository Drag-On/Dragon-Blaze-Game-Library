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
project (DBGL_CORE C CXX)

######################################################################
### Configure compilation details
######################################################################

#set (CMAKE_BUILD_TYPE Release)

set (DBGL_CORE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include") 								# Path to own headers
set (DBGL_CORE_LIB_DIR "${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}") 						# Path to own library file
set (DBGL_PLATFORM_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../DBGL_Platform/include") 			# Path to platform headers
set (DBGL_PLATFORM_LIB_DIR "${PROJECT_SOURCE_DIR}/../DBGL_Platform/${CMAKE_BUILD_TYPE}") 	# Path to platform library file

######################################################################
### Platform specific stuff
######################################################################
if(WIN32)
	set (DBGL_CORE_LIB_NAME "libDBGL_Core.dll")
	set (DBGL_CORE_DLL_NAME "libDBGL_Core.dll")
	set (DBGL_PLATFORM_LIB_NAME "libDBGL_Platform.dll")
	set (DBGL_PLATFORM_DLL_NAME "libDBGL_Platform.dll")
elseif(UNIX)
	set (DBGL_CORE_LIB_NAME "libDBGL_Core.so")
	set (DBGL_CORE_DLL_NAME "libDBGL_Core.so")
	set (DBGL_PLATFORM_LIB_NAME "libDBGL_Platform.so")
	set (DBGL_PLATFORM_DLL_NAME "libDBGL_Platform.so")
endif()

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
file(GLOB_RECURSE SRC
    "include/*.h"
    "src/*.cpp"
)

######################################################################
### Add target for doxygen
######################################################################
if(NOT DEFINED GRAPHVIZ_INSTALLED)
	set(GRAPHVIZ_INSTALLED NO)
endif(NOT DEFINED GRAPHVIZ_INSTALLED)
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
include_directories(${DBGL_CORE_INCLUDE_DIR})
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_library(DBGL_Core SHARED ${SRC})
set_target_properties(DBGL_Core PROPERTIES LINKER_LANGUAGE CXX)

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_Core "${DBGL_PLATFORM_LIB_DIR}/${DBGL_PLATFORM_LIB_NAME}")

######################################################################
### Compile tests
######################################################################
if(COMPILE_TESTS)
	add_subdirectory("${PROJECT_SOURCE_DIR}/test/"
					 "${PROJECT_BINARY_DIR}/test/")
endif(COMPILE_TESTS)