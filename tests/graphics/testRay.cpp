#include "catch.hpp"

#include "graphics/ray.h"
#include "math/transformations.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("ray should work")
{
    SECTION("creating a ray should work")
    {
        auto origin = point(1, 2, 3);
        auto direction = vector(4, 5, 6);

        ray r {origin, direction};

        REQUIRE(r.origin() == origin);
        REQUIRE(r.direction() == direction);
    }

    SECTION("ray ray_position should work")
    {
        ray r {point(2, 3, 4), vector(1, 0, 0)};

        REQUIRE(r.position(0) == point(2, 3, 4));
        REQUIRE(r.position(1) == point(3, 3, 4));
        REQUIRE(r.position(-1) == point(1, 3, 4));
        REQUIRE(r.position(2.5) == point(4.5, 3.0, 4.0));
    }

    SECTION("ray ray_transform should work")
    {
        ray r { point(1, 2, 3), vector(0, 1, 0) };
        auto m = translation(3, 4, 5);
        auto r2 = r.transform(m);
        REQUIRE(r2.origin() == point(4, 6, 8));
        REQUIRE(r2.direction() == vector(0, 1, 0));

        auto m2 = scaling(2, 3, 4);
        auto r3 = r.transform(m2);
        REQUIRE(r3.origin() == point(2, 6, 12));
        REQUIRE(r3.direction() == vector(0, 3, 0));

    }

}
