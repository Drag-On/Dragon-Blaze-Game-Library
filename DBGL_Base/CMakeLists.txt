CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (DBGL_Base C CXX)
# The version number.
SET (DBGL_VERSION_MAJOR 0)
SET (DBGL_VERSION_MINOR 1)
 
# configure a header file to pass some of the CMake settings
# to the source code
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/include/DBGL_Base_Config.h.in"
  "${PROJECT_SOURCE_DIR}/include/DBGL_Base_Config.h"
  )

# enable C++11
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++0x")
ENDIF()
 
# add the library
FILE(GLOB_RECURSE Base_Src
    "include/*.h"
    "src/*.cpp"
)

# include the right directory
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib/glfw/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib/glew/include")

# OpenGL
FIND_PACKAGE(OpenGL)
IF (OPENGL_FOUND)
	MESSAGE("OpenGL Correctly Found")
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE (OPENGL_FOUND)
	MESSAGE("OpenGL environment missing")
ENDIF (OPENGL_FOUND)

ADD_LIBRARY(DBGL_Base SHARED ${Base_Src})
TARGET_LINK_LIBRARIES(DBGL_Base "${PROJECT_SOURCE_DIR}/lib/glew/lib/libglew32.dll.a")
TARGET_LINK_LIBRARIES(DBGL_Base "${PROJECT_SOURCE_DIR}/lib/glfw/src/glfw3dll.a")
TARGET_LINK_LIBRARIES(DBGL_Base "${OPENGL_LIBRARIES}")
SET_TARGET_PROPERTIES(DBGL_Base PROPERTIES LINKER_LANGUAGE CXX)

# External examples
add_subdirectory("${PROJECT_SOURCE_DIR}/Examples/"
				 "${PROJECT_SOURCE_DIR}/Examples/")