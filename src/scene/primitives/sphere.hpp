#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "primitive.hpp"
#include "glm/glm.hpp"

/**
 * \brief Sphere primitives in the scene
 */
class Sphere : public Primitive {
public:
    /**
     * @brief Create a sphere
     * @param radius Radius of the sphere
     * @param center Center position of the sphere
     */
    Sphere(float radius, glm::vec3 center);

    /*! Test if ray intersects with the sphere or not (in object space), if
     * so, return a pointer to the geometry of intersection point and normal.
     */
    virtual bool intersect(const Ray& ray,
                           Hit &hit) const override;

private:
    float radius_;
    glm::vec3 center_;

};


#endif // SPHERE_HPP
