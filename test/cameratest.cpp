#include "catch.hpp"

#include "../src/camera.hpp"
#include "../src/math/math.hpp"

using glm::vec3;

TEST_CASE( "Camera ray generation at origin", "[Camera]" ) {
    vec3 origin(0, 0, 0);
    vec3 lookat(0, 0, 1);
    vec3 up(0, 1, 0);
    vec3 left(-1, 0, 0);
    float fov = 30;

    Camera camera(origin, lookat, up, fov);
    Ray ray;

    Resolution resolution1(10, 20);
    SECTION( "Generate ray at screen center" ) {
        camera.generateRay(resolution1, Sample(5, 10), ray);
        Ray expectation = Ray(origin, lookat - origin);
        REQUIRE( ray.origin() == expectation.origin() );
        CHECK( ray.direction().x == Approx(expectation.direction().x) );
        CHECK( ray.direction().y == Approx(expectation.direction().y) );
        CHECK( ray.direction().z == Approx(expectation.direction().z) );
    }

    SECTION( "Generate ray at left side" ) {
        camera.generateRay(resolution1, Sample(0, 10), ray);
        Ray expectation = Ray(origin, lookat - origin);
        expectation.setDirection(lookat - left * tanf(Math::radian(fov / 2)) / 2.0f);
        REQUIRE( ray.origin() == expectation.origin() );
        CHECK( ray.direction().x == Approx(expectation.direction().x) );
        CHECK( ray.direction().y == Approx(expectation.direction().y) );
        CHECK( ray.direction().z == Approx(expectation.direction().z) );
    }

    SECTION( "Generate ray at top side" ) {
        camera.generateRay(resolution1, Sample(5, 0), ray);
        Ray expectation = Ray(origin, lookat - origin);
        expectation.setDirection(lookat - up * tanf(Math::radian(fov / 2)));
        REQUIRE( ray.origin() == expectation.origin() );
        CHECK( ray.direction().x == Approx(expectation.direction().x) );
        CHECK( ray.direction().y == Approx(expectation.direction().y) );
        CHECK( ray.direction().z == Approx(expectation.direction().z) );
    }
}
