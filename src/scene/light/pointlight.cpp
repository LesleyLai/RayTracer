#include "pointlight.hpp"

#include "../hit.hpp"
#include "../../ray.hpp"

PointLight::PointLight(glm::vec3 position, ColorRGB color) :
    position_{position},
    color_{color} {

}

void PointLight::generateLightRay(const glm::vec3 &position,
                                        Ray &lightRay,
                                        ColorRGB &lightcolor) const {
    lightRay = Ray(position, this->position_ - position);
    lightcolor = color_;
}
