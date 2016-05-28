#include <iostream>

#include "blinnphongshader.hpp"

BlinnPhongShader::BlinnPhongShader()
{

}

ColorRGB BlinnPhongShader::shading(const Hit &hit,
                                         const Ray &inputray,
                                         const Ray &lightRay,
                                         const ColorRGB &lightColor,
                                         const PhongIlluminationInfo &illuminationinfo,
                                         bool shadowed) {
    auto emission = illuminationinfo.emissionComponent();
    auto ambient = illuminationinfo.ambientComponent();

    auto color = emission + ambient;

    if (!shadowed) {
        auto n = glm::normalize(hit.normal());
        auto l = glm::normalize(lightRay.direction());
        auto inputDir = glm::normalize(inputray.direction());

        auto shininess = illuminationinfo.shininess();
        auto diffuse = illuminationinfo.diffuseComponent();
        auto specular = illuminationinfo.specularComponent();

        // lambert
        auto nDotL= glm::dot(n, l);
        auto lambert = lightColor * diffuse * std::max(nDotL, 0.0f);

        // specular
        auto half = glm::normalize(l - inputDir);
        auto nDotH = glm::dot(n, half);
        auto phong = lightColor * specular * std::pow(nDotH, shininess);

        color += lambert;
        color += phong;
    }

    return color;
}
