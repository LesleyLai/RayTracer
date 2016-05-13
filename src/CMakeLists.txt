
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

add_executable(RayTracer main.cpp)

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

set_subdir_sources(
    )
