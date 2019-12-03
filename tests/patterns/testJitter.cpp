#include "catch.hpp"

#include "patterns/jitter.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("jitter functions should work")
{
    SECTION("add_jitter should work")
    {
       REQUIRE(add_jitter(point(1, 2, 3)) == point(1, 2, 3));
       auto expected = add_jitter(point(1.1, 2.2, 3));
       REQUIRE(expected.x == Approx(1.12653).margin(1e-5));
       REQUIRE(expected.y == Approx(2.20167).margin(1e-5));
       REQUIRE(expected.z == Approx(3.04741).margin(1e-5));
    }
}
