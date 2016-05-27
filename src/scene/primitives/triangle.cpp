#include <iostream>

#include "triangle.hpp"
#include "../../math/math.hpp"

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) : vertices_ {a, b, c} {

}

bool Triangle::intersect(const Ray &ray,
                         Hit &hit) const {
    /*
     * The implementation of this method consults "Fundamentals Of Computer
     * Graphics 3rd edition" 4.4.2 Ray-Triangle Intersection as a reference
     */

    auto vd = ray.direction();
    auto ve = ray.origin();
    auto va = vertices_[0];
    auto vb = vertices_[1];
    auto vc = vertices_[2];

    auto a = va.x-vb.x;
    auto b = va.y-vb.y;
    auto c = va.z-vb.z;
    auto d = va.x-vc.x;
    auto e = va.y-vc.y;
    auto f = va.z-vc.z;
    auto g = vd.x;
    auto h = vd.y;
    auto i = vd.z;
    auto j = va.x-ve.x;
    auto k = va.y-ve.y;
    auto l = va.z-ve.z;

    auto eiMinusHf = e*i - h*f;
    auto gfMinusDi = g*f - d*i;
    auto dhMinusEg = d*h - e*g;
    auto akMinusJb = a*k - j*b;
    auto jcMinusAl = j*c - a*l;
    auto blMinusKc = b*l - k*c;


    float M = a*(eiMinusHf)+b*(gfMinusDi)+c*(dhMinusEg);

    // compute t
    float t = -(f*akMinusJb + e*jcMinusAl + d*blMinusKc) / M;
    if ((t < 0) || (t > hit.t())) return false;

    // compute gamma
    float gamma = (i*akMinusJb + h*jcMinusAl + g*blMinusKc) / M;
    if ((gamma < 0) || (gamma > 1)) return false;

    // compute beta
    float beta = (j*eiMinusHf + k*gfMinusDi + l*dhMinusEg) / M;
    if ((beta < 0) || (beta > (1 - gamma))) return false;

    auto n = triangleNormal();

    hit = Hit(n, t);
    return true;


}

glm::vec3 Triangle::triangleNormal() const {
    return glm::normalize(glm::cross(vertices_[1] - vertices_[0], vertices_[2] - vertices_[0]));
}
