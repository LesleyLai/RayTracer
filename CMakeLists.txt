project (RayTracer)
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


# CPP Flags
set(CXX_FLAGS "-Wall -std=c++11 -Wno-missing-braces")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_definitions(${CXX_FLAGS})

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# GLM
include_directories("./lib/glm")


# FreeImage Header
if (WIN32)
    include_directories("./lib/FreeImage/distrib/windows/${EX_PLATFORM_NAME}")
    message("./lib/FreeImage/distrib/windows/${EX_PLATFORM_NAME}")
elseif (APPLE)
    # TODO: Support mac
else()
    find_package(FreeImage REQUIRED)
    include_directories(${FREEIMAGE_INCLUDE_DIRS})
endif()

add_library (Source_Code ${SRC_LIST})
add_executable(RayTracer src/main.cpp)
target_link_libraries (RayTracer Source_Code)

# FreeImage Library
if (WIN32)
    target_link_libraries(RayTracer "${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeImage/distrib/windows/${EX_PLATFORM_NAME}/FreeImage.lib")
elseif (APPLE)
    # TODO: Support mac
else()
    target_link_libraries(RayTracer ${FREEIMAGE_LIBRARY})
endif()

source_group(required REGULAR_EXPRESSION required/.*)
source_group(required\\ REGULAR_EXPRESSION required/pass/.*)

# Copy dlls
if (WIN32)
        add_custom_command(TARGET RayTracer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeImage/distrib/windows/${EX_PLATFORM_NAME}/FreeImage.dll" "$<TARGET_FILE_DIR:RayTracer>")
endif()


enable_testing ()
add_subdirectory(test)
