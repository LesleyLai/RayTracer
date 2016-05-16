#include "blinnphongshader.hpp"

BlinnPhongShader::BlinnPhongShader()
{

}

ColorRGB BlinnPhongShader::shading(const LocalGeometry &local,
                                         const Ray &inputray,
                                         const Ray &lightRay,
                                         const ColorRGB &lightColor,
                                         const PhongIlluminationInfo &illuminationinfo) {
    auto n = local.normal();
    auto l = lightRay.direction();

    auto half = glm::normalize(l - inputray.direction());

    float shininess = illuminationinfo.shininess();

    auto diffuse = illuminationinfo.diffuseComponent();
    auto specular = illuminationinfo.specularComponent();

    auto lambert = lightColor * diffuse * std::max(glm::dot(n, l), 0.0f);
    auto phong = lightColor * specular * std::pow(std::max(glm::dot(n, half), 0.0f), shininess);

    return lambert + phong;
}
