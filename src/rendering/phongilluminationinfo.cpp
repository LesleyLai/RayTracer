#include "phongilluminationinfo.hpp"

PhongIlluminationInfo::PhongIlluminationInfo() :
    diffuseComponent_{ColorRGB(1, 1, 1)},
    specularComponent_{ColorRGB(1, 1, 1)},
    ambientComponent_{ColorRGB(.2, .2, .2)},
    mirrorComponent_{ColorRGB(1, 1, 1)},
    shininess_{1}
{

}

PhongIlluminationInfo::PhongIlluminationInfo(ColorRGB &diffuse,
                                             ColorRGB &specular,
                                             ColorRGB &ambient,
                                             ColorRGB &mirror,
                                             float shininess) :
    diffuseComponent_{diffuse},
    specularComponent_{specular},
    ambientComponent_{ambient},
    mirrorComponent_{mirror},
    shininess_{shininess} {

}

ColorRGB PhongIlluminationInfo::diffuseComponent() const
{
    return diffuseComponent_;
}

void PhongIlluminationInfo::setDiffuseComponent(const ColorRGB &diffuseComponent)
{
    diffuseComponent_ = diffuseComponent;
}

ColorRGB PhongIlluminationInfo::specularComponent() const
{
    return specularComponent_;
}

void PhongIlluminationInfo::setSpecularComponent(const ColorRGB &specularComponent)
{
    specularComponent_ = specularComponent;
}

ColorRGB PhongIlluminationInfo::ambientComponent() const
{
    return ambientComponent_;
}

void PhongIlluminationInfo::setAmbientComponent(const ColorRGB &ambientComponent)
{
    ambientComponent_ = ambientComponent;
}

ColorRGB PhongIlluminationInfo::mirrorComponent() const
{
    return mirrorComponent_;
}

void PhongIlluminationInfo::setMirrorComponent(const ColorRGB &mirrorComponent)
{
    mirrorComponent_ = mirrorComponent;
}

float PhongIlluminationInfo::shininess() const
{
    return shininess_;
}

void PhongIlluminationInfo::setShininess(float shininess)
{
    shininess_ = shininess;
}
