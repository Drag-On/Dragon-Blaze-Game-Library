cmake_minimum_required (VERSION 2.6)
project (DBGL_Base_Test C CXX)

# enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
 
# add the library
file(GLOB_RECURSE Base_Src
    "include/*.h"
    "src/*.cpp"
)

# Copy library over
add_custom_command(	OUTPUT "${PROJECT_SOURCE_DIR}/Debug/libDBGL_Base.a"
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${PROJECT_SOURCE_DIR}/../DBGL_Base/Debug/libDBGL_Base.a"
					"${PROJECT_SOURCE_DIR}/Debug/libDBGL_Base.a"
					)
set_property(SOURCE ${Base_Src} APPEND PROPERTY OBJECT_DEPENDS libDBGL_Base.a)

add_executable(DBGL_Base_Test ${Base_Src})
#set_target_properties(DBGL_Base_Test PROPERTIES LINKER_LANGUAGE CXX)

include_directories("${PROJECT_SOURCE_DIR}/../DBGL_Base/include/")
target_link_libraries (DBGL_Base_Test "${PROJECT_SOURCE_DIR}/Debug/libDBGL_Base.a")