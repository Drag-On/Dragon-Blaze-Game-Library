CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (DBGL_Base_Examples C CXX)

# External examples
add_subdirectory("${PROJECT_SOURCE_DIR}/Basics"
				 "${PROJECT_SOURCE_DIR}/Basics")
add_subdirectory("${PROJECT_SOURCE_DIR}/Movement"
				 "${PROJECT_SOURCE_DIR}/Movement")
add_subdirectory("${PROJECT_SOURCE_DIR}/Shader"
				 "${PROJECT_SOURCE_DIR}/Shader")