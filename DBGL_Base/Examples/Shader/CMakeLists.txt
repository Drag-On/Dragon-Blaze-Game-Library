CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (DBGL_Base_Shader C CXX)

# enable C++11
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()
 
# add the source code
FILE(GLOB Basic_Example_Src
    "*.h"
    "*.cpp"
)

# create a list of files to copy
SET(Libraries2Copy
   "${PROJECT_SOURCE_DIR}/../../Debug/libDBGL_Base.dll"
   "${PROJECT_SOURCE_DIR}/../../lib/glew/lib/glew32.dll"
   "${PROJECT_SOURCE_DIR}/../../lib/glfw/src/glfw3.dll"
)

# OpenGL
FIND_PACKAGE(OpenGL)
IF (OPENGL_FOUND)
	MESSAGE("OpenGL Correctly Found")
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE (OPENGL_FOUND)
	MESSAGE("OpenGL environment missing")
ENDIF (OPENGL_FOUND)

ADD_EXECUTABLE(DBGL_Base_Shader ${Basic_Example_Src})

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../include/")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../lib/glfw/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../lib/glew/include")

TARGET_LINK_LIBRARIES(DBGL_Base_Shader "${PROJECT_SOURCE_DIR}/libDBGL_Base.dll")
TARGET_LINK_LIBRARIES(DBGL_Base_Shader "${OPENGL_LIBRARIES}")

ADD_CUSTOM_TARGET(Always_execute_shader ALL)
ADD_DEPENDENCIES(DBGL_Base_Shader Always_execute_shader)

# do the copying
FOREACH(file_i ${Libraries2Copy})
	ADD_CUSTOM_COMMAND(TARGET Always_execute_shader
                        PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file_i} "${PROJECT_SOURCE_DIR}"
                        DEPENDS ${file_i}
                        )
ENDFOREACH(file_i)