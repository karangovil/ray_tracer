
#include "catch.hpp"

#include "sphere.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("sphere should work")
{
    SECTION("creating a default sphere should work")
    {
        sphere s;
        REQUIRE(s.radius() == 1.0);
        REQUIRE(s.center() == point(0.0, 0.0, 0.0));
    }
    
    SECTION("creating a sphere should work")
    {
        double radius = 5.0;
        tuple<double> center {1.0, 2.0, 3.0};
        sphere s {center, radius};
        REQUIRE(s.radius() == radius);
        REQUIRE(s.center() == center);
    }
}
