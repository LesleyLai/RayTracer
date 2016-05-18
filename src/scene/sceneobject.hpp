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
                           std::unique_ptr<LocalGeometry> &local,
                   float &last_t_cache) const;


    Material material() const;

    void setMaterial(const Material &material);

private:
    Material material_;

    std::vector<std::shared_ptr<Primitive>> primitives_;

};

#endif // SCENEOBJECT_HPP
