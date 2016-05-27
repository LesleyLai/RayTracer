#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "glm/glm.hpp"

#include "light.hpp"
#include "../../color.hpp"
#include "../../ray.hpp"


/**
 * \brief Class for point light sources in the scene
 */
class PointLight : public Light {
public:
    explicit PointLight(glm::vec3 position, ColorRGB color);

    virtual void generateLightRay(const glm::vec3 &position,
                                  Ray& lightRay,
                                  ColorRGB& lightcolor) const override;

private:
    glm::vec3 position_;
    ColorRGB color_;

};



#endif // DIRECTIONALLIGHT_HPP
