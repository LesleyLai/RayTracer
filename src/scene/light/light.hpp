#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../../color.hpp"

class LocalGeometry;
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
     * \param local The position of where the light ray started
     * \param lightRay The generated ray
     * \param lightcolor The generated light color
     */
    virtual void generateLightRay(const LocalGeometry& local,
                                  Ray& lightRay,
                                  ColorRGB& lightcolor) const = 0;
};

#endif // LIGHT_HPP
