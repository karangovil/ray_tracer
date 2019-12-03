#include "catch.hpp"

#include "math/perlin.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("perlin noise should work")
{
    SECTION("plain noise should work")
    {
        perlin& p = perlin::getInstance();
        REQUIRE(p.noise(1, 2, 3) == 0);
        REQUIRE(p.noise(1.1, 2.2, 3) == Approx(0.23153).margin(1e-5));
    }
    
    SECTION("octave noise should work")
    {
        perlin& p = perlin::getInstance();
        REQUIRE(p.octaveNoise(1, 2, 3, 8) == 0);
        REQUIRE(p.octaveNoise(1.1, 2.2, 3, 8) == Approx(0.13265).margin(1e-5));
    }

}
