#include "catch.hpp"

#include "graphics/colors.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("points and vectors should work")
{
    SECTION("colors should work")
    {
        color c { -0.5, 0.4, 1.7 };
        REQUIRE(c.red == -0.5);
        REQUIRE(c.green == 0.4);
        REQUIRE(c.blue == 1.7);
    }

    SECTION("colors should add")
    {
        color c1 { 0.9, 0.6, 0.75 };
        color c2 { 0.7, 0.1, 0.25 };
        REQUIRE((c1 + c2) == color { 1.6, 0.7, 1.0 });
    }
    
    SECTION("colors should subtract")
    {
        color c1 { 0.9, 0.6, 0.75 };
        color c2 { 0.7, 0.1, 0.25 };
        REQUIRE((c1 - c2) == color { 0.2, 0.5, 0.5 });
    }
    
    SECTION("colors should multiply")
    {
        color c1 { 1, 0.2, 0.4 };
        color c2 { 0.9, 1, 0.1 };
        REQUIRE((c1 * c2) == color { 0.9, 0.2, 0.04 });
    }

}
