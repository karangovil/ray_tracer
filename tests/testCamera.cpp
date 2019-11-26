#include "catch.hpp"

#include "graphics/camera.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("camera should work")
{
    SECTION("camera initialization should work")
    {
        camera c {160, 120, M_PI / 2.0};
        REQUIRE(c.hsize() == 160);
        REQUIRE(c.vsize() == 120);
        REQUIRE(c.fov() == M_PI / 2.0);
        REQUIRE(c.transform() == matrix4x4<double> {});
    }
}
