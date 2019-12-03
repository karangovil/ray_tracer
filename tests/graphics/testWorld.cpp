#include "catch.hpp"

#include "graphics/world.h"
#include "graphics/ray.h"
#include "graphics/intersection.h"
#include "shapes/sphere.h"
#include "math/transformations.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("world should work")
{
    SECTION("world initialization should work")
    {
        world w;
        point_light light {point(-10.0, 10.0, -10.0), color {1.0f, 1.0f, 1.0f}};

        auto objs = w.objs();

        REQUIRE(w.light() == light);

        sphere s1 {material {0.1, 0.7, 0.2, 200.0, {0.8f, 1.0f, 0.6f}}};
        sphere s2 {};
        s2.set_transform(scaling(0.5, 0.5, 0.5));

        REQUIRE(dynamic_cast<sphere&>(*w.objs()[0]) == s1);
        REQUIRE(dynamic_cast<sphere&>(*w.objs()[1]) == s2);

        sphere s3 {material {0.2, 0.5, 0.9, 100.0, {0.4f, 1.0f, 0.4f}}};
        std::shared_ptr<object> o = std::make_shared<sphere>(s3);
        w.add_obj(o);
        REQUIRE(dynamic_cast<sphere&>(*w.objs()[2]) == s3);
    }

    SECTION("world intersection should work")
    {
        world w;
        ray r {point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};

        auto xs = intersect_world(w, r);

        REQUIRE(xs.has_value());
        auto ints = xs.value();
        REQUIRE(ints.size() == 4);
        REQUIRE(ints[0].t() == 4.0);
        REQUIRE(ints[1].t() == 4.5);
        REQUIRE(ints[2].t() == 5.5);
        REQUIRE(ints[3].t() == 6.0);
    }
}
