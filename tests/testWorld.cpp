#include "catch.hpp"

#include "graphics/world.h"
#include "graphics/ray.h"
#include "graphics/intersection.h"

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

        auto s1 = std::make_shared<sphere> (material {0.1, 0.7, 0.2, 200.0, {0.8f, 1.0f, 0.6f}});
        std::shared_ptr<object> s2 = std::make_shared<sphere>();
        s2->set_transform(scaling(0.5, 0.5, 0.5));
        
        REQUIRE(w.objs().find(s1) != w.objs().end());
        REQUIRE(w.objs().find(s2) != w.objs().end());
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
