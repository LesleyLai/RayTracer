#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "primitive.hpp"

class Triangle : public Primitive {
public:
    /**
     * @brief Create a triangle
     */
    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);

    /*! Test if ray intersects with the triangle or not (in object space), if
     * so, return a pointer to the geometry of intersection point and normal.
     */
    virtual bool intersect(const Ray& ray,
                           std::unique_ptr<LocalGeometry> &local,
                           float &last_t_cache) const override;

private:
    glm::vec3 vertices_[3];

    glm::vec3 triangleNormal() const;
};

#endif // TRIANGLE_HPP
