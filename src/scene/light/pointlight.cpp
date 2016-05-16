#include "pointlight.hpp"

#include "../localgeometry.hpp"
#include "../../ray.hpp"

PointLight::PointLight(glm::vec3 position, ColorRGB color) :
    position_{position},
    color_{color} {

}

void PointLight::generateLightRay(const LocalGeometry &local,
                                        Ray &lightRay,
                                        ColorRGB &lightcolor) const {
    lightRay = Ray(local.position(), position_ - local.position());
    lightcolor = color_;
}
