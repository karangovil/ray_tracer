#include "catch.hpp"

#include "graphics/light.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("light should work")
{
    SECTION("point light source should work")
    {
        color intensity {1.0, 1.0, 1.0};
        auto position = point(0.0, 0.0, 0.0);
        point_light light {position, intensity};

        REQUIRE(light.position() == position);
        REQUIRE(light.intensity() == intensity);
    }

}
