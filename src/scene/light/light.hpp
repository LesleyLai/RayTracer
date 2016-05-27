#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm/glm.hpp"

#include "../../color.hpp"

class Hit;
class Ray;

/**
 * \brief Abstract class for light sources in the scene
 */
class Light {
public:
    Light() {}

    /*!
     * \brief This is an abstract class that will generate a ray starting from
     * the position stored in local to the position of the light source.
     * \param position The position of where the light ray started
     * \param lightRay The generated ray
     * \param lightcolor The generated light color
     */
    virtual void generateLightRay(const glm::vec3 &position,
                                  Ray& lightRay,
                                  ColorRGB& lightcolor) const = 0;
};

#endif // LIGHT_HPP
