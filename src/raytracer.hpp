#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include "ray.hpp"
#include "color.hpp"

class Scene;

class RayTracer {
public:
    explicit RayTracer(Scene &inputScene, int maxDepth);

    ///
    /// \brief The main recursive ray tracing function
    /// \param inputRay
    /// \param color
    ///
    void trace(Ray& inputRay, ColorRGB& color);

private:
    void _trace(Ray& inputRay, int depth, ColorRGB& color);

    /*! \brief Reference back to the scene.
     */
    Scene &scene_;

    int maxDepth_;
};

#endif // RAYTRACER_HPP
