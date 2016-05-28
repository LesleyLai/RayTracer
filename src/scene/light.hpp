#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm/glm.hpp"

#include "../ray.hpp"
#include "../color.hpp"

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

/**
 * \brief Class for directional light sources in the scene
 */
class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 direction, ColorRGB color) :
        direction_{direction},
        color_{color} {
    }

    virtual void generateLightRay(const glm::vec3 &position,
                                  Ray& lightRay,
                                  ColorRGB& lightcolor) const override {
        lightRay = Ray(position, this->direction_);
        lightcolor = color_;
    }

private:
    glm::vec3 direction_;
    ColorRGB color_;
};

/**
 * \brief Class for point light sources in the scene
 */
class PointLight : public Light {
public:
    PointLight(glm::vec3 position, ColorRGB color) :
        position_{position},
        color_{color} {
    }

    virtual void generateLightRay(const glm::vec3 &position,
                                  Ray& lightRay,
                                  ColorRGB& lightcolor) const override {
        lightRay = Ray(position, this->position_ - position);
        lightcolor = color_;
    }

private:
    glm::vec3 position_;
    ColorRGB color_;

};

#endif // LIGHT_HPP
