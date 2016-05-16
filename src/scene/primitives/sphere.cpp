#include "sphere.hpp"
#include "../../math/math.hpp"

using namespace Math;

Sphere::Sphere(float radius, glm::vec3 center) :
    radius_{radius},
    center_{center} {
}

bool Sphere::intersect(const Ray &ray, std::unique_ptr<LocalGeometry> &local, float &last_t_cache) const {
    auto c = center_;
    auto e = ray.origin();
    auto d = ray.direction();

    auto dDotec = dot(d, e - c);
    auto dDotd = dot(d, d);

    auto deltaSquire = dDotec * dDotec - dDotd *
            (dot(e - c, e - c) - radius_ * radius_);
    if (deltaSquire < 0) return false;

    auto delta = std::sqrt(deltaSquire);
    auto negdDotec = dot(-d, e - c);

    if (negdDotec - delta > 0) {
        auto t = (negdDotec - delta) / dDotd;

        if (last_t_cache < t) return false;
        last_t_cache = t;

        glm::vec3 p = e + d * t;

        local = std::unique_ptr<LocalGeometry>(new LocalGeometry(p, p - c));
        return true;
    }
    return false;
}
