#ifndef LOCALGEOMETRY_HPP
#define LOCALGEOMETRY_HPP

#include "glm/glm.hpp"


/*!
 * \brief Stores the local geometry at the intersection point.
 */
class LocalGeometry {
public:
    LocalGeometry(glm::vec3 position, glm::vec3 normal);

    glm::vec3 position() const;
    void setPosition(const glm::vec3 &position);

    glm::vec3 normal() const;
    void setNormal(const glm::vec3 &normal);

private:
    glm::vec3 position_;
    glm::vec3 normal_;
};

#endif // LOCALGEOMETRY_HPP
