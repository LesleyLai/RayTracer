#include "catch.hpp"

#include <iostream>

#include "../src/color.hpp"

TEST_CASE( "RGB float colors", "[Color]" ) {
    ColorRGB white(1, 1, 1);
    ColorRGB black(0, 0, 0);
    ColorRGB red(1, 0, 0);
    ColorRGB blue(0, 0, 1);

    SECTION( "Addition of RGB float colors" ) {
        auto tmp = red + blue;
        REQUIRE( tmp == ColorRGB(1, 0, 1) );
    }

    SECTION( "Subtraction of RGB float colors" ) {
        auto tmp = white - blue;
        REQUIRE( tmp == ColorRGB(1, 1, 0) );
    }

    SECTION( "Scalar multiplication" ) {
        auto tmp = white * .42;
        REQUIRE( tmp.r == Approx(.42) );
        REQUIRE( tmp.g == Approx(.42) );
        REQUIRE( tmp.b == Approx(.42) );
    }

    SECTION( "Color multiply with another color" ) {
        ColorRGB grey(.5, .5, .5);
        ColorRGB lightGrey(.2, .3, .4);
        auto tmp = grey * lightGrey;

        REQUIRE( tmp.r == Approx(.1) );
        REQUIRE( tmp.g == Approx(.15) );
        REQUIRE( tmp.b == Approx(.2) );
    }

    SECTION( "Color can be clamped when value overflowed" ) {
        white += ColorRGB(.1, .1, .1);

        REQUIRE( white == ColorRGB(1, 1, 1) );

        black -= ColorRGB(.5, .5, .5);

        REQUIRE( black == ColorRGB(0, 0, 0) );
    }

}
