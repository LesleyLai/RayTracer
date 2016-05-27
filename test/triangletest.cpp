#include "catch.hpp"

#include "../src/scene/primitives/triangle.hpp"

using glm::vec3;

TEST_CASE( "Triangle intersection with rays", "[Triangle]" ) {
    vec3 a(-1, -1, 1);
    vec3 b(1, -1, 1);
    vec3 c(1, 1, 1);

    Triangle tri(a, b, c);
    std::unique_ptr<Hit> hit;
    float t = std::numeric_limits<float>::infinity();

    SECTION( "Intersects when the ray cross over the triangle" ) {
        Ray ray(vec3(0.5, -0.5, 0), vec3(0, 0, 1));
        vec3 expecthit = vec3(0.5, -0.5, 1);

        //auto intersect = tri.intersect(ray, hit, t);
        //REQUIRE(intersect == true);
        //CHECK(hit->position().x == expecthit.x);
        //CHECK(hit->position().y == expecthit.y);
        //CHECK(hit->position().z == expecthit.z);
        //CHECK(t == glm::distance(hit->position(), ray.origin()));
    }

    SECTION( "Intersects when the ray cross over a line of the triangle" ) {
        Ray ray(vec3(0, 0, 0), vec3(0, 0, 1));
        vec3 expecthit = vec3(0, 0, 1);

        //auto intersect = tri.intersect(ray, hit, t);
        //REQUIRE(intersect == true);
        //CHECK(hit->position().x == expecthit.x);
        //CHECK(hit->position().y == expecthit.y);
        //CHECK(hit->position().z == expecthit.z);
        //CHECK(t == glm::distance(hit->position(), ray.origin()));
    }

    SECTION( "Does not intersect when the triangle is behand the ray origin" ) {
        Ray ray(vec3(0, 0, 0), vec3(0, 0, -1));

        //auto intersect = tri.intersect(ray, hit, t);
        //REQUIRE(intersect == false);
        //CHECK(t == std::numeric_limits<float>::infinity()); // checks whether t is not updated
        //CHECK(hit == nullptr); // Checks whether hit is not updated
    }

    SECTION( "Does not intersect when there are already a closer intersection detect" ) {
        float t_near = .1f;
        Ray ray(vec3(0, 0, 0), vec3(0, 0, 1));

        //auto intersect = tri.intersect(ray, hit, t_near);
        //REQUIRE(intersect == false);
        //CHECK(t_near == .1f);
        //CHECK(hit == nullptr);
    }

    SECTION( "Does not intersect when the ray do not cross over the triangle" ) {

        SECTION("up") {
            Ray ray(vec3(0, 0, 0), vec3(0, 3, 1));

            //auto intersect = tri.intersect(ray, hit, t);
            //REQUIRE(intersect == false);
            //CHECK(t == std::numeric_limits<float>::infinity());
            //CHECK(hit == nullptr);
        }

        SECTION("left") {
            Ray ray(vec3(0, 0, 0), vec3(3, 0, 1));

            //auto intersect = tri.intersect(ray, hit, t);
            //REQUIRE(intersect == false);
            //CHECK(t == std::numeric_limits<float>::infinity());
            //CHECK(hit == nullptr);
        }
    }
}
