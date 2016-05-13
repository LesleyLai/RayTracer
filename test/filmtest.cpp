#include "catch.hpp"

#include "../src/film.hpp"

TEST_CASE( "Can commit color to buffer in the Film Class", "[Film]" ) {
    Film film(200, 200);

    SECTION( "Do not throw exceptions when commit not out of bound" ) {
        REQUIRE_NOTHROW(film.commit(199, 199, ColorRGB(0, 0, 0)));
    }

    SECTION( "Exceptions when try to commit out of bound" ) {
        REQUIRE_THROWS_AS(film.commit(200, 200, ColorRGB(0, 0, 0)), std::out_of_range);
    }
}
