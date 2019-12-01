#include "catch.hpp"

#include <math.h>

#include "testObject.h"
#include "graphics/intersection.h"
#include "math/transformations.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("testObject should work")
{
    SECTION("default testObject should work")
    {
        test_object o {};
        REQUIRE(o.transform() == matrix4x4 {});

        o.set_transform(translation(2, 3, 4));
        REQUIRE(o.transform() == translation(2, 3, 4));

        REQUIRE(o.mat() == material {});
        material m;
        m.set_ambient(1);
        o.set_material(m);
        REQUIRE(o.mat() == m);
    }

    SECTION("intersecting a ray with a scaled test object should work")
    {
        test_object o {};
        o.set_transform(scaling(2, 2, 2));
        ray r {point(0, 0, -5), vector(0, 0, 1)};
        o.intersect(r);
        // REQUIRE(o.saved_ray().origin() == point(0, 0, -2.5));
        REQUIRE(o.saved_ray().direction() == vector(0, 0, 0.5));
    }
    
    SECTION("intersecting a ray with a translated test object should work")
    {
        test_object o {};
        o.set_transform(translation(5, 0, 0));
        ray r {point(0, 0, -5), vector(0, 0, 1)};
        o.intersect(r);
        REQUIRE(o.saved_ray().origin() == point(-5, 0, -5));
        REQUIRE(o.saved_ray().direction() == vector(0, 0, 1));
    }
    
    SECTION("normal on a translated test object should work")
    {
        test_object o {};
        o.set_transform(translation(0, 1, 0));
        auto n = o.normal_at(point(0, 1.70711, -0.70711));
        REQUIRE(n.x == 0_a);
        REQUIRE(n.y == 0.70711_a);
        REQUIRE(n.z == -0.70711_a);
    }
    
    SECTION("normal on a transformed test object should work")
    {
        test_object o {};
        o.set_transform(scaling(1, 0.5, 1) * rotation_z(M_PI / 5));
        auto n = o.normal_at(point(0, sqrt(2) / 2, -sqrt(2) / 2));
        REQUIRE(n.x == 0_a);
        REQUIRE(n.y == 0.97014_a);
        REQUIRE(n.z == Approx(-0.24254).margin(5));
    }

}
