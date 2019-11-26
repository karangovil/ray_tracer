#include "catch.hpp"

#include "graphics/colors.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("points and vectors should work")
{
    SECTION("colors should work")
    {
        color<float> c { -0.5, 0.4, 1.7 };
        REQUIRE(c.red == -0.5f);
        REQUIRE(c.green == 0.4f);
        REQUIRE(c.blue == 1.7f);
    }

    SECTION("colors should add")
    {
        color<float> c1 { 0.9, 0.6, 0.75 };
        color<float> c2 { 0.7, 0.1, 0.25 };
        REQUIRE((c1 + c2) == color<float> { 1.6, 0.7, 1.0 });
    }
    
    SECTION("colors should subtract")
    {
        color<float> c1 { 0.9, 0.6, 0.75 };
        color<float> c2 { 0.7, 0.1, 0.25 };
        REQUIRE((c1 - c2) == color<float> { 0.2, 0.5, 0.5 });
    }
    
    SECTION("colors should multiply")
    {
        color<float> c1 { 1, 0.2, 0.4 };
        color<float> c2 { 0.9, 1, 0.1 };
        REQUIRE((c1 * c2) == color<float> { 0.9, 0.2, 0.04 });
    }

}
