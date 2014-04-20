CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (DBGL_Base_Test C CXX)

# enable C++11
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")
ENDIF()
 
# add the source code
FILE(GLOB_RECURSE Base_Src
    "include/*.h"
    "src/*.cpp"
)

# create a list of files to copy
SET(Libraries2Copy
   "${PROJECT_SOURCE_DIR}/../DBGL_Base/Debug/libDBGL_Base.dll"
   "${PROJECT_SOURCE_DIR}/../DBGL_Base/lib/glew/lib/glew32.dll"
   "${PROJECT_SOURCE_DIR}/../DBGL_Base/lib/glfw/src/glfw3.dll"
)

# OpenGL
FIND_PACKAGE(OpenGL)
IF (OPENGL_FOUND)
	MESSAGE("OpenGL Correctly Found")
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE (OPENGL_FOUND)
	MESSAGE("OpenGL environment missing")
ENDIF (OPENGL_FOUND)

ADD_EXECUTABLE(DBGL_Base_Test ${Base_Src})

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../DBGL_Base/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../DBGL_Base/lib/glfw/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../DBGL_Base/lib/glew/include")

TARGET_LINK_LIBRARIES(DBGL_Base_Test "${PROJECT_SOURCE_DIR}/Debug/libDBGL_Base.dll")
#TARGET_LINK_LIBRARIES(DBGL_Base_Test "${PROJECT_SOURCE_DIR}/lib/glew/lib/libglew32.dll.a")
#TARGET_LINK_LIBRARIES(DBGL_Base_Test "${PROJECT_SOURCE_DIR}/lib/glfw/src/libglfw3.a")
TARGET_LINK_LIBRARIES(DBGL_Base_Test "${OPENGL_LIBRARIES}")

ADD_CUSTOM_TARGET(Always_execute ALL)
ADD_DEPENDENCIES(DBGL_Base_Test Always_execute)

# do the copying
FOREACH(file_i ${Libraries2Copy})
	ADD_CUSTOM_COMMAND(TARGET Always_execute
                        PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file_i} "${PROJECT_SOURCE_DIR}/Debug/"
                        DEPENDS ${file_i}
                        )
ENDFOREACH(file_i)