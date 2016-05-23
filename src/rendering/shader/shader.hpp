#ifndef SHADER_HPP
#define SHADER_HPP

#include "../../math/math.hpp"
#include "../../color.hpp"
#include "../../ray.hpp"
#include "../../scene/localgeometry.hpp"
#include "../../rendering/material.hpp"

/*!
 * \brief Interfaces with the shader program.
 */
class Shader
{
public:
    Shader() {}

    virtual ColorRGB shading(const LocalGeometry& local,
                                   const Ray &inputray,
                                   const Ray &lightRay,
                                   const ColorRGB &lightColor,
                                   const PhongIlluminationInfo &lightinfo,
                                   bool shadowed) = 0;
};

#endif // SHADER_HPP
