#ifndef RAY_HPP
#define RAY_HPP

#include "../glm/glm/glm.hpp"

/**
 * @brief Representation of rays.
 *
 * A ray is an infinite line starting at origin and going in some direction.
 */
class Ray {
public:
    /**
      * \brief Default constructor of a ray
      *
      * Creates a ray starting at (0, 0, 0) along z.
      */
    Ray() :
        origin_{glm::vec3{}},
        direction_{glm::vec3(0, 0, 1)}
    {}

    /**
      * \brief Creates a ray starting at origin along direction.
      */
    Ray(glm::vec3 origin, glm::vec3 direction) :
        origin_{origin},
        direction_{direction} {
        glm::normalize(direction_);
    }

    /**
      * \brief Gets origin of the ray.
      */
    glm::vec3 origin() const {
        return origin_;
        }

    /**
      * \brief Sets origin of the ray.
      */
    void setOrigin(const glm::vec3 origin) {
        origin_ = origin;
        }

    /**
      * \brief Gets direction of the ray.
      */
    glm::vec3 direction() const {
        return direction_;
        }

    /**
      * \brief Sets direction of the ray.
      *
      * Direction is always a normalized vector. If you assign a vector of non unit length, it will be normalized.
      */
    void setDirection(const glm::vec3 direction) {
        direction_ = glm::normalize(direction);
    }

    /**
      * \brief Transforms the ray
      */
    friend Ray operator* (const glm::mat4& transform, Ray rhs) {
        glm::vec3 origin(transform * glm::vec4(rhs.origin_, 1));
        glm::vec3 direction(transform * glm::vec4(rhs.direction_, 1));
        return Ray(origin, direction);
    }

private:
    glm::vec3 origin_; //The origin glm::vec3 of the ray.
    glm::vec3 direction_; // The direction of the ray.
};

#endif // RAY_HPP
