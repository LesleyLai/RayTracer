#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "phongilluminationinfo.hpp"
#include "../color.hpp"

struct Material
{
public:
    Material();
    Material(PhongIlluminationInfo lightInfo);

    PhongIlluminationInfo IlluminationInfo_;
};

#endif // MATERIAL_HPP
