#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "ray.hpp"
#include "sampler/sample.hpp"

/// Resolution of the camera on screen
using Resolution = glm::vec2;

class Camera
{
public:
    Camera(const glm::vec3& center,
           const glm::vec3& direction,
           const glm::vec3& up, float fov);

    /**
     * \brief Create a ray starting from the camera that passes through the
     * corresponding pixel on the image plane.
     * \param resolution Resolution of the camera on screen
     * \param sample
     * \param ray
     */
    void generateRay(const Resolution &resolution, const Sample &sample, Ray& ray) const;

private:
    glm::vec3 center_;
    glm::vec3 direction_;
    glm::vec3 horizontal_;
    glm::vec3 up_;

    int width_;
    int height_;

    float fov_;
};

#endif // CAMERA_HPP
