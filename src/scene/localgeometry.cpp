#include "localgeometry.hpp"

LocalGeometry::LocalGeometry(glm::vec3 position, glm::vec3 normal) :
    position_{position},
    normal_{glm::normalize(normal)} {
}

glm::vec3 LocalGeometry::position() const
{
    return position_;
}

void LocalGeometry::setPosition(const glm::vec3 &position)
{
    position_ = position;
}

glm::vec3 LocalGeometry::normal() const
{
    return normal_;
}

void LocalGeometry::setNormal(const glm::vec3 &normal) {
    normal_ = glm::normalize(normal);
}

