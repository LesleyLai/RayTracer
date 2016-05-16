#ifndef PHONGILLUMINATIONINFO_HPP
#define PHONGILLUMINATIONINFO_HPP

#include "../color.hpp"

class PhongIlluminationInfo {
public:
    PhongIlluminationInfo();

    PhongIlluminationInfo(ColorRGB &diffuse,
                          ColorRGB &specular,
                          ColorRGB &ambient,
                          ColorRGB &mirror,
                          float shininess);

    ColorRGB diffuseComponent() const;
    void setDiffuseComponent(const ColorRGB &diffuseComponent);

    ColorRGB specularComponent() const;
    void setSpecularComponent(const ColorRGB &specularComponent);

    ColorRGB ambientComponent() const;
    void setAmbientComponent(const ColorRGB &ambientComponent);

    ColorRGB mirrorComponent() const;
    void setMirrorComponent(const ColorRGB &mirrorComponent);

    float shininess() const;
    void setShininess(float shininess);

private:
    ColorRGB diffuseComponent_;
    ColorRGB specularComponent_;
    ColorRGB ambientComponent_;
    ColorRGB mirrorComponent_;

    float shininess_;
};

#endif // PHONGILLUMINATIONINFO_HPP
