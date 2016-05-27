#include "glm/gtc/matrix_inverse.hpp"

#include "sceneobject.hpp"

SceneObject::SceneObject(const Material &material) :
    material_{material},
    transform_{glm::mat4()},
    inverse_transform_{glm::mat4()} {
}

void SceneObject::addPrimitive(std::shared_ptr<Primitive> primitive) {
    if (!primitive) {
        return;
    }
    primitives_.emplace_back(std::move(primitive));
}

bool SceneObject::intersect(const Ray &ray) const {
    Ray changedRay = inverse_transform_ * ray;

    for (std::shared_ptr<Primitive> primitive_ptr : primitives_) {
        if (primitive_ptr->intersect(changedRay)) return true;
    }
    return false;
}

bool SceneObject::intersect(const Ray &ray,
                            Hit &hit) const {
    bool intersect_flag = false;
    Ray changedRay = inverse_transform_ * ray;

    for (std::shared_ptr<Primitive> primitive_ptr : primitives_) {
        if (primitive_ptr->intersect(changedRay, hit)) {
            intersect_flag = true;
        }
    }
    return intersect_flag;
}

Material SceneObject::material() const {
    return material_;
}

void SceneObject::setMaterial(const Material &material) {
    material_ = material;
}

glm::mat4 SceneObject::transform() const {
    return transform_;
}


glm::mat4 SceneObject::inverse_transform() const {
    return inverse_transform_;
}


void SceneObject::setTransform(const glm::mat4 &transform) {
    transform_ = transform;
    inverse_transform_ = glm::inverse(transform);
}
