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
    SECTION( "Generates ray at screen center" ) {
        camera.generateRay(resolution1, Sample(5, 10), ray);
        Ray expectation = Ray(origin, lookat - origin);
        REQUIRE( ray.origin() == expectation.origin() );
        CHECK( ray.direction().x == Approx(expectation.direction().x) );
        CHECK( ray.direction().y == Approx(expectation.direction().y) );
        CHECK( ray.direction().z == Approx(expectation.direction().z) );
    }

    SECTION( "Generates ray to left side of the screen" ) {
        camera.generateRay(resolution1, Sample(0, 10), ray);
        Ray expectation = Ray(origin, lookat - origin);
        expectation.setDirection(lookat - left * tanf(Math::radian(fov / 2)) / 2.0f);
        REQUIRE( ray.origin() == expectation.origin() );
        CHECK( ray.direction().x == Approx(expectation.direction().x) );
        CHECK( ray.direction().y == Approx(expectation.direction().y) );
        CHECK( ray.direction().z == Approx(expectation.direction().z) );
    }

    SECTION( "Generates ray to top side of the screen" ) {
        camera.generateRay(resolution1, Sample(5, 0), ray);
        Ray expectation = Ray(origin, lookat - origin);
        expectation.setDirection(lookat - up * tanf(Math::radian(fov / 2)));
        REQUIRE( ray.origin() == expectation.origin() );
        CHECK( ray.direction().x == Approx(expectation.direction().x) );
        CHECK( ray.direction().y == Approx(expectation.direction().y) );
        CHECK( ray.direction().z == Approx(expectation.direction().z) );
    }
}
