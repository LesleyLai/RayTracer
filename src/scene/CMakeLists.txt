add_subdirectory(primitives)
add_subdirectory(light)

set_subdir_sources(
    scene.hpp
    scene.cpp
    sceneobject.hpp
    sceneobject.cpp
    hit.hpp
    hit.cpp
    )
