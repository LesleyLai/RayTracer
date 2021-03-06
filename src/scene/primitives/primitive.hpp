#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <memory>
#include <limits>

#include "../../ray.hpp"
#include "../../scene/hit.hpp"

/**
 * \brief Abstract class for primitives in the scene
 */
class Primitive
{
public:
    Primitive() {}

    /*! Test if ray intersects with the primitive or not (in object space), if
     * so, return a pointer to the geometry of intersection point and normal.
     */
    virtual bool intersect(const Ray& ray,
                           Hit &hit) const = 0;

    /// \brief Just return true if the primitive intersect with the ray
    bool intersect(const Ray& ray) const {
        Hit hit(glm::vec3(), std::numeric_limits<float>::infinity());
        return this->intersect(ray, hit);
    }
};

#endif // PRIMITIVE_HPP
