cmake_minimum_required (VERSION 2.6)
project (DBGL_Base_Test C CXX)

# enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
 
# add the source code
file(GLOB_RECURSE Base_Src
    "include/*.h"
    "src/*.cpp"
)

# create a list of files to copy
set(LIBRARIES2COPY
   "${PROJECT_SOURCE_DIR}/../DBGL_Base/Debug/libDBGL_Base.dll"
   "${PROJECT_SOURCE_DIR}/../DBGL_Base/lib/glew/lib/glew32.dll"
)

# OpenGL
find_package(OpenGL)
if (OPENGL_FOUND)
	MESSAGE("OpenGL Correctly Found")
	include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
	MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)

add_executable(DBGL_Base_Test ${Base_Src})

include_directories("${PROJECT_SOURCE_DIR}/../DBGL_Base/include/")
include_directories("${PROJECT_SOURCE_DIR}/../DBGL_Base/lib/glfw/include")
include_directories("${PROJECT_SOURCE_DIR}/../DBGL_Base/lib/glew/include")

target_link_libraries(DBGL_Base_Test "${PROJECT_SOURCE_DIR}/Debug/libDBGL_Base.dll")
#target_link_libraries(DBGL_Base_Test "${PROJECT_SOURCE_DIR}/lib/glew/lib/libglew32.dll.a")
#target_link_libraries(DBGL_Base_Test "${PROJECT_SOURCE_DIR}/lib/glfw/src/libglfw3.a")
target_link_libraries(DBGL_Base_Test "${OPENGL_LIBRARIES}")

# do the copying
foreach(file_i ${LIBRARIES2COPY})
    add_custom_command(
		TARGET DBGL_Base_Test
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND}
		ARGS -E copy_if_different ${file_i} "${PROJECT_SOURCE_DIR}/Debug/"
	)
endforeach(file_i)