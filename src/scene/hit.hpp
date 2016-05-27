#ifndef LOCALGEOMETRY_HPP
#define LOCALGEOMETRY_HPP

#include "glm/glm.hpp"


/*!
 * \brief Stores the local geometry information at the intersection point.
 */
class Hit {
public:
    Hit(glm::vec3 normal, float t);

    glm::vec3 normal() const;
    void setNormal(const glm::vec3 &normal);

    float t() const;

private:
    glm::vec3 normal_;

    float t_;
};

#endif // LOCALGEOMETRY_HPP
