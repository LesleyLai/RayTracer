#include "catch.hpp"

#include "../src/scene/primitives/triangle.hpp"

using glm::vec3;

TEST_CASE( "Triangle intersection with rays", "[Triangle]" ) {
    vec3 a(-1, -1, 1);
    vec3 b(1, -1, 1);
    vec3 c(1, 1, 1);

    Triangle tri(a, b, c);
    std::unique_ptr<LocalGeometry> local;
    float t = std::numeric_limits<float>::infinity();

    SECTION( "Intersects when the ray cross over the triangle" ) {
        Ray ray(vec3(0.5, -0.5, 0), vec3(0, 0, 1));
        vec3 expectLocal = vec3(0.5, -0.5, 1);

        auto intersect = tri.intersect(ray, local, t);
        REQUIRE(intersect == true);
        CHECK(local->position().x == expectLocal.x);
        CHECK(local->position().y == expectLocal.y);
        CHECK(local->position().z == expectLocal.z);
        CHECK(t == glm::distance(local->position(), ray.origin()));
    }

    SECTION( "Intersects when the ray cross over a line of the triangle" ) {
        Ray ray(vec3(0, 0, 0), vec3(0, 0, 1));
        vec3 expectLocal = vec3(0, 0, 1);

        auto intersect = tri.intersect(ray, local, t);
        REQUIRE(intersect == true);
        CHECK(local->position().x == expectLocal.x);
        CHECK(local->position().y == expectLocal.y);
        CHECK(local->position().z == expectLocal.z);
        CHECK(t == glm::distance(local->position(), ray.origin()));
    }

    SECTION( "Does not intersect when the triangle is behand the ray origin" ) {
        Ray ray(vec3(0, 0, 0), vec3(0, 0, -1));

        auto intersect = tri.intersect(ray, local, t);
        REQUIRE(intersect == false);
        CHECK(t == std::numeric_limits<float>::infinity()); // checks whether t is not updated
        CHECK(local == nullptr); // Checks whether local is not updated
    }

    SECTION( "Does not intersect when there are already a closer intersection detect" ) {
        float t_near = .1f;
        Ray ray(vec3(0, 0, 0), vec3(0, 0, 1));

        auto intersect = tri.intersect(ray, local, t_near);
        REQUIRE(intersect == false);
        CHECK(t_near == .1f);
        CHECK(local == nullptr);
    }

    SECTION( "Does not intersect when the ray do not cross over the triangle" ) {

        SECTION("up") {
            Ray ray(vec3(0, 0, 0), vec3(0, 3, 1));

            auto intersect = tri.intersect(ray, local, t);
            REQUIRE(intersect == false);
            CHECK(t == std::numeric_limits<float>::infinity());
            CHECK(local == nullptr);
        }

        SECTION("left") {
            Ray ray(vec3(0, 0, 0), vec3(3, 0, 1));

            auto intersect = tri.intersect(ray, local, t);
            REQUIRE(intersect == false);
            CHECK(t == std::numeric_limits<float>::infinity());
            CHECK(local == nullptr);
        }
    }
}
