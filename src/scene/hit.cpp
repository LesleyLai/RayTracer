#include "hit.hpp"

Hit::Hit(glm::vec3 normal, float t) :
    normal_{glm::normalize(normal)},
    t_{t} {
}


glm::vec3 Hit::normal() const
{
    return normal_;
}

void Hit::setNormal(const glm::vec3 &normal) {
    normal_ = glm::normalize(normal);
}

float Hit::t() const
{
    return t_;
}
