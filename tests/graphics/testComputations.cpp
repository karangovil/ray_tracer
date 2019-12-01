#include "catch.hpp"

#include "graphics/computations.h"
#include "graphics/ray.h"
#include "graphics/intersection.h"
#include "math/transformations.h"
#include "shapes/sphere.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("world should work")
{
    SECTION("computations initialization should work")
    {
        ray r {point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
        std::shared_ptr<object> s = std::make_shared<sphere>();
        intersection i {s, 4.0};

        computations c {i, r};

        REQUIRE(c.t() == i.t());
        REQUIRE(c.obj() == i.obj());
        REQUIRE(c.point() == point(0.0, 0.0, -1.0));
        REQUIRE(c.eye_v() == vector(0.0, 0.0, -1.0));
        REQUIRE(c.normal_v() == vector(0.0, 0.0, -1.0));
        REQUIRE_FALSE(c.inside());
    }

    SECTION("computations initialization inside should work")
    {
        ray r {point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0)};
        std::shared_ptr<object> s = std::make_shared<sphere>();
        intersection i {s, 1.0};

        computations c {i, r};

        REQUIRE(c.t() == i.t());
        REQUIRE(c.obj() == i.obj());
        REQUIRE(c.point() == point(0.0, 0.0, 1.0));
        REQUIRE(c.eye_v() == vector(0.0, 0.0, -1.0));
        REQUIRE(c.normal_v() == vector(0.0, 0.0, -1.0));
        REQUIRE(c.inside());
    }

    SECTION("over_point should work")
    {
        ray r {point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
        std::shared_ptr<object> s = std::make_shared<sphere>();
        s->set_transform(translation(0.0, 0.0, 1.0));
        intersection i {s, 5.0};
        computations c {i, r};
        REQUIRE(c.over_point().z < -TOLERANCE_F / 2.0);
        REQUIRE(c.point().z > c.over_point().z);
    }
}
