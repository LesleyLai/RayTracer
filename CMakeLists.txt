project (TEST)
cmake_minimum_required(VERSION 2.8)

# Check system
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE(STATUS "64 bits compiler detected" )
    SET( EX_PLATFORM 64 )
    SET( EX_PLATFORM_NAME "x64" )
    SET( EX_PLATFORM_STR "64" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE(STATUS "32 bits compiler detected" )
    SET( EX_PLATFORM 32 )
    SET( EX_PLATFORM_NAME "x86" )
    SET( EX_PLATFORM_STR "32" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

# Import utility cmake scripts.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/util/Prepend.cmake)

add_subdirectory(src)

enable_testing ()
add_subdirectory(test)
