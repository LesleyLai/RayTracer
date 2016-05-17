add_subdirectory(math)
add_subdirectory(parser)
add_subdirectory(scene)
add_subdirectory(sampler)
add_subdirectory(rendering)

set_subdir_sources(
    camera.hpp
    camera.cpp
    color.hpp
    imageExportor.hpp
    imageExportor.cpp
    film.hpp
    film.cpp
    ray.hpp
    raytracer.hpp
    raytracer.cpp
    )


