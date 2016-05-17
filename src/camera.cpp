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
    // Create the coordinate frame of the camera
}

void Camera::generateRay(const Resolution& resolution, const Sample& sample, Ray &ray) const {
    auto halfAngleY = fov_ / 2;

    auto halfSizeY = tan(halfAngleY);
    auto halfSizeX = halfSizeY / resolution.y * resolution.x;

    auto halsResolutionX = resolution.x / 2;
    auto halsResolutionY = resolution.y / 2;

    float u = halfSizeX * (sample.x - halsResolutionX) / (halsResolutionX);
    float v = halfSizeY * (sample.y - halsResolutionY) / (halsResolutionY);

    ray.setOrigin(center_);
    ray.setDirection(direction_ + (u*horizontal_) + (v*up_));
}
