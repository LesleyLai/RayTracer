#include "sceneobject.hpp"

SceneObject::SceneObject(Material &material) : material_{material} {
}

void SceneObject::addPrimitive(std::shared_ptr<Primitive> primitive) {
    if (!primitive) {
        return;
    }
    primitives_.emplace_back(std::move(primitive));
}

bool SceneObject::intersect(const Ray &ray) const {
    for (std::shared_ptr<Primitive> primitive_ptr : primitives_) {
        if (primitive_ptr->intersect(ray)) return true;
    }
    return false;
}

bool SceneObject::intersect(const Ray &ray, std::unique_ptr<LocalGeometry> &local, float &last_t_cache) const {
    bool intersect_flag = false;
    for (std::shared_ptr<Primitive> primitive_ptr : primitives_) {
        if (primitive_ptr->intersect(ray, local, last_t_cache)) intersect_flag = true;
    }
    return intersect_flag;
}

Material SceneObject::material() const
{
    return material_;
}

void SceneObject::setMaterial(const Material &material)
{
    material_ = material;
}
