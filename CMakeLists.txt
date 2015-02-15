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
project (DBGL C CXX)

######################################################################
### Configure compilation details
######################################################################
set (DBGL_LIB_DIR "${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}") 			# Path to DBGL library files
set (DBGL_PLATFORM_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/DBGL_Platform/include") 	# Path to platform headers
set (DBGL_CORE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/DBGL_Core/include") 		# Path to core headers
set (DBGL_RESOURCES_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/DBGL_Resources/include")	# Path to resources headers
#set (CMAKE_BUILD_TYPE Release)

######################################################################
### Platform specific stuff
######################################################################
if(WIN32)
    set (DBGL_PLATFORM_LIB_NAME "libDBGL_Platform.dll")
    set (DBGL_PLATFORM_DLL_NAME "libDBGL_Platform.dll")
    set (DBGL_CORE_LIB_NAME "libDBGL_Core.dll")
    set (DBGL_CORE_DLL_NAME "libDBGL_Core.dll")
    set (DBGL_RESOURCES_LIB_NAME "libDBGL_Resources.dll")
    set (DBGL_RESOURCES_DLL_NAME "libDBGL_Resources.dll")
elseif(UNIX)
    set (DBGL_PLATFORM_LIB_NAME "libDBGL_Platform.so")
    set (DBGL_PLATFORM_DLL_NAME "libDBGL_Platform.so")
    set (DBGL_CORE_LIB_NAME "libDBGL_Core.so")
    set (DBGL_CORE_DLL_NAME "libDBGL_Core.so")
    set (DBGL_RESOURCES_LIB_NAME "libDBGL_Resources.so")
    set (DBGL_RESOURCES_DLL_NAME "libDBGL_Resources.so")
endif()

######################################################################
### Set policy
### This suppresses warnings that occur because all the projects
### build into the same directory. This way it is possible that files
### get overwritten by projects later in the build chain! Check for
### better option!
######################################################################
cmake_policy(SET CMP0013 OLD)

######################################################################
### Set module path
######################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

######################################################################
### Compiler flags
######################################################################
# GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11") # C++11
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")
endif(CMAKE_COMPILER_IS_GNUCXX)
if(UNIX)
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -ldl")
endif(UNIX)
# TODO: Other compilers

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
### Find packages
######################################################################
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)

######################################################################
### Include directories
######################################################################
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})
include_directories(${DBGL_CORE_INCLUDE_DIR})
include_directories(${DBGL_RESOURCES_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_PATH})

######################################################################
### Debug messages
######################################################################
message("##### Paths #####")
message("DBGL_LIB_DIR: ${DBGL_LIB_DIR}")
message("DBGL_PLATFORM_INCLUDE_DIR: ${DBGL_PLATFORM_INCLUDE_DIR}")
message("DBGL_CORE_INCLUDE_DIR: ${DBGL_CORE_INCLUDE_DIR}")
message("DBGL_RESOURCES_INCLUDE_DIR: ${DBGL_RESOURCES_INCLUDE_DIR}")
message("GLFW_INCLUDE_DIR: ${GLFW_INCLUDE_DIR}")
message("GLEW_INCLUDE_PATH: ${GLEW_INCLUDE_PATH}")
message("OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
message("##### Files #####")
message("DBGL_PLATFORM_LIB_NAME: ${DBGL_PLATFORM_LIB_NAME}")
message("DBGL_PLATFORM_DLL_NAME: ${DBGL_PLATFORM_DLL_NAME}")
message("DBGL_CORE_LIB_NAME: ${DBGL_CORE_LIB_NAME}")
message("DBGL_CORE_DLL_NAME: ${DBGL_CORE_DLL_NAME}")
message("DBGL_RESOURCES_LIB_NAME: ${DBGL_RESOURCES_LIB_NAME}")
message("DBGL_RESOURCES_DLL_NAME: ${DBGL_RESOURCES_DLL_NAME}")
message("GLFW_LIBRARY: ${GLFW_LIBRARY}")
message("GLEW_LIBRARY: ${GLEW_LIBRARY}")
message("#################")

######################################################################
### Check which projects to compile
######################################################################
if(NOT (COMPILE_PLATFORM OR COMPILE_CORE OR COMPILE_RESOURCES))
    set(COMPILE_ALL "YES")
else(NOT (COMPILE_PLATFORM OR COMPILE_CORE OR COMPILE_RESOURCES))
    set(COMPILE_ALL "NO")
endif(NOT (COMPILE_PLATFORM OR COMPILE_CORE OR COMPILE_RESOURCES))
message("##### Flags #####")
message("COMPILE_PLATFORM: ${COMPILE_PLATFORM}")
message("COMPILE_CORE: ${COMPILE_CORE}")
message("COMPILE_RESOURCES: ${COMPILE_RESOURCES}")
message("COMPILE_ALL: ${COMPILE_ALL}")
message("COMPILE_TESTS: ${COMPILE_TESTS}")
message("#################")

######################################################################
### Subprojects
######################################################################
#### Platform
if(COMPILE_PLATFORM OR COMPILE_ALL)
    add_subdirectory("${PROJECT_SOURCE_DIR}/DBGL_Platform/"
                     "${PROJECT_BINARY_DIR}")
    if(COMPILE_TESTS)
        add_subdirectory("${PROJECT_SOURCE_DIR}/DBGL_Platform/test/"
                         "${PROJECT_BINARY_DIR}/test/")
    endif(COMPILE_TESTS)
endif(COMPILE_PLATFORM OR COMPILE_ALL)
#### Core
if(COMPILE_CORE OR COMPILE_ALL)
    add_subdirectory("${PROJECT_SOURCE_DIR}/DBGL_Core/"
                     "${PROJECT_BINARY_DIR}")
    if(COMPILE_TESTS)
        add_subdirectory("${PROJECT_SOURCE_DIR}/DBGL_Core/test/"
                         "${PROJECT_BINARY_DIR}/test/")
    endif(COMPILE_TESTS)
endif(COMPILE_CORE OR COMPILE_ALL)
#### Resources
if(COMPILE_RESOURCES OR COMPILE_ALL)
    add_subdirectory("${PROJECT_SOURCE_DIR}/DBGL_Resources/"
                     "${PROJECT_BINARY_DIR}")
    if(COMPILE_TESTS)
        add_subdirectory("${PROJECT_SOURCE_DIR}/DBGL_Resources/test/"
                         "${PROJECT_BINARY_DIR}/test/")
    endif(COMPILE_TESTS)
endif(COMPILE_RESOURCES OR COMPILE_ALL)
