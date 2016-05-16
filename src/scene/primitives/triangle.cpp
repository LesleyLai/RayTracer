#include "triangle.hpp"
#include "../../math/math.hpp"

using namespace Math;

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) : vertices_ {a, b, c} {

}

bool Triangle::intersect(const Ray &ray, std::unique_ptr<LocalGeometry> &local, float &last_t_cache) const {
    auto a = vertices_[0];
    auto b = vertices_[1];
    auto c = vertices_[2];


    auto e = ray.origin();
    auto d = ray.direction();
    auto n = triangleNormal();

    auto tmp = glm::dot(d, n);
    // Ray is parallel to the triangle plane
    if (std::abs(tmp) < .001) return false;

    auto t = (glm::dot(a, n) - glm::dot(e, n)) / tmp;

    if (t < 0 || last_t_cache < t) return false;
    auto p = e + d * t;

    auto beta = ((a.y - b.y) * p.x + (b.x - a.x) * p.y + a.x * b.y - b.x * a.y) /
            ((a.y - b.y) * c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y);

    if (beta < 0 || beta > 1) return false;

    auto gamma = ((a.y - c.y) * p.x + (c.x - a.x) * p.y + a.x * c.y - c.x * a.y) /
            ((a.y - c.y) * b.x + (c.x - a.x) * b.y + a.x * c.y - c.x * a.y);

    if (gamma < 0 || gamma > 1 - beta) return false;



    last_t_cache = t;
    local = std::unique_ptr<LocalGeometry>(new LocalGeometry(p, n));
    return true;


}

glm::vec3 Triangle::triangleNormal() const {
    return glm::normalize(glm::cross(vertices_[1] - vertices_[0], vertices_[2] - vertices_[0]));
}
