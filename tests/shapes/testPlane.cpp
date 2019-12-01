#include "catch.hpp"

#include "shapes/plane.h"
#include "math/tuple.h"
#include "graphics/ray.h"
#include "graphics/intersection.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("plane should work")
{
    SECTION("default plane should work")
    {
        plane p {};
        REQUIRE(p.normal_at(point(0, 0, 0)) == vector(0, 1, 0));
        REQUIRE(p.normal_at(point(10, 0, -10)) == vector(0, 1, 0));
        REQUIRE(p.normal_at(point(-5, 0, 150)) == vector(0, 1, 0));
    }

    SECTION("plane intersection with a parallel ray should work")
    {
        plane p {};
        ray r {point(0, 10, 0), vector(0, 0, 1)};
        REQUIRE_FALSE(p.intersect(r).has_value());
    }
    
    SECTION("plane intersection with a coplanar ray should work")
    {
        plane p {};
        ray r {point(0, 0, 0), vector(0, 0, 1)};
        REQUIRE_FALSE(p.intersect(r).has_value());
    }

    SECTION("plane intersection with a ray above should work")
    {
        std::shared_ptr<object> p = std::make_shared<plane>();
        ray r {point(0, 1, 0), vector(0, -1, 0)};
        REQUIRE(p->intersect(r).has_value());
        REQUIRE(p->intersect(r).value().size() == 1);
        REQUIRE(p->intersect(r).value()[0].t() == 1);
        REQUIRE(p->intersect(r).value()[0].obj() == p);
    }

    SECTION("plane intersection with a ray below should work")
    {
        std::shared_ptr<object> p = std::make_shared<plane>();
        ray r {point(0, -1, 0), vector(0, 1, 0)};
        REQUIRE(p->intersect(r).has_value());
        REQUIRE(p->intersect(r).value().size() == 1);
        REQUIRE(p->intersect(r).value()[0].t() == 1);
        REQUIRE(p->intersect(r).value()[0].obj() == p);
    }

}
