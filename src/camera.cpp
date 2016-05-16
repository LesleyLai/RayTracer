#include "iostream"

#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "math/math.hpp"

Camera::Camera(
               const glm::vec3& center,
               const glm::vec3& direction,
               const glm::vec3& up,
               float fov) :
    center_{center},
    direction_{glm::normalize(direction)}, //w
    horizontal_{glm::normalize(glm::cross(direction_, up))}, //u
    up_{glm::cross(horizontal_, direction_)}, //v
    fov_{fov} {
}

void Camera::generateRay(const Resolution& resolution, Sample sample, Ray &ray) const {
    auto halfAngle = fov_ / 2.0f;
    auto halfSize = tan(halfAngle);
    auto size = 2 * halfSize;
    float d = 1.0f;


    float u = -halfSize + size * sample.y / resolution.y;
    float v = -halfSize + size * sample.x / resolution.x;

    ray.setOrigin(center_);
    ray.setDirection((d*direction_) + (u*horizontal_) + (v*up_));
}
