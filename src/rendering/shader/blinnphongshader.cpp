#include <iostream>

#include "blinnphongshader.hpp"

BlinnPhongShader::BlinnPhongShader()
{

}

ColorRGB BlinnPhongShader::shading(const LocalGeometry &local,
                                         const Ray &inputray,
                                         const Ray &lightRay,
                                         const ColorRGB &lightColor,
                                         const PhongIlluminationInfo &illuminationinfo,
                                         bool shadowed) {
    auto n = local.normal();
    auto l = lightRay.direction();

    auto half = glm::normalize(l - inputray.direction());

    float shininess = illuminationinfo.shininess();

    auto emission = illuminationinfo.emissionComponent();
    auto ambient = illuminationinfo.ambientComponent();

    auto color = emission + ambient;

    if (shadowed) {
        auto diffuse = illuminationinfo.diffuseComponent();
        auto specular = illuminationinfo.specularComponent();

        auto nDotL= glm::dot(n, l);
        auto lambert = lightColor * diffuse * std::max(nDotL, 0.0f);

        auto nDotH = glm::dot(n, half);
        auto phong = lightColor * specular * std::pow(std::max(nDotH, 0.0f), shininess);

        color += lambert;
        color += phong;
    }

    return color;
}
