######################################################################
### Dragon Blaze Game Library
###
### Copyright (c) 2015 by Jan Moeller
###
### This software is provided "as-is" and does not claim to be
### complete or free of bugs in any way. It should work, but
### it might also begin to hurt your kittens.
######################################################################

######################################################################
### Project code files
######################################################################
file(GLOB_RECURSE SRC_FILES
    "DBGL_Platform/test/OSTests/LibraryTest/*.cpp"
)

######################################################################
### Include directories
######################################################################
include_directories(${DBGL_PLATFORM_INCLUDE_DIR})

######################################################################
### Make target
######################################################################
add_executable(DBGL_PLATFORM_TEST_OS_MODULE ${SRC_FILES})

######################################################################
### Link libraries
######################################################################
target_link_libraries(DBGL_PLATFORM_TEST_OS_MODULE DBGL_Platform)
