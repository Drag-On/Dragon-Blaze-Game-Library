cmake_minimum_required (VERSION 2.6)
project (DBGL_Base C CXX)
# The version number.
set (DBGL_VERSION_MAJOR 0)
set (DBGL_VERSION_MINOR 1)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/include/DBGL_Base_Config.h.in"
  "${PROJECT_SOURCE_DIR}/include/DBGL_Base_Config.h"
  )

# enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
 
# add the library
file(GLOB_RECURSE Base_Src
    "include/*.h"
    "src/*.cpp"
)

# include the right directory
include_directories("${PROJECT_SOURCE_DIR}/include")

# OpenGL
find_package(OpenGL)

add_library(DBGL_Base ${Base_Src})
TARGET_LINK_LIBRARIES(DBGL_Base ${OPENGL_LIBRARIES})
set_target_properties(DBGL_Base PROPERTIES LINKER_LANGUAGE CXX)