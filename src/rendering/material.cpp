#include "material.hpp"

Material::Material() : IlluminationInfo_{PhongIlluminationInfo()} {

}

Material::Material(PhongIlluminationInfo lightInfo) : IlluminationInfo_{lightInfo}
{

}
