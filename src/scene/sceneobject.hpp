#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <memory>
#include <vector>

#include "../rendering/material.hpp"

#include "primitives/primitive.hpp"

/*! \brief Represents a generic object that will live in the 3D world that we call our Scene.
 */
class SceneObject {
public:
    SceneObject(const Material &material);

    /*! \brief Adds a new Primitive to the SceneObject.
     *  \param primitive The primitive to add.
     */
    void addPrimitive(std::shared_ptr<Primitive> primitive);

    /// \brief Return true if the object intersect with the ray
    bool intersect(const Ray& ray) const;

    /*! Test if ray intersects with the object or not (in object space), if
     * so, return a pointer to the geometry of intersection point and normal.
     */
    bool intersect(const Ray& ray,
                           Hit &hit) const;


    Material material() const;

    void setMaterial(const Material &material);


    glm::mat4 transform() const;
    glm::mat4 inverse_transform() const;

    void setTransform(const glm::mat4 &transform);

private:
    Material material_;

    glm::mat4 transform_;
    glm::mat4 inverse_transform_;

    std::vector<std::shared_ptr<Primitive>> primitives_;
};

#endif // SCENEOBJECT_HPP
