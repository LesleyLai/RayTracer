#ifndef BLINNPHONGSHADER_HPP
#define BLINNPHONGSHADER_HPP


#include "shader.hpp"

class BlinnPhongShader : public Shader {
public:
    BlinnPhongShader();

    virtual ColorRGB shading(const LocalGeometry& local,
                                   const Ray &inputray,
                                   const Ray &lightRay,
                                   const ColorRGB &lightColor,
                                   const PhongIlluminationInfo &illuminationinfo) override;
};

#endif // BLINNPHONGSHADER_HPP
