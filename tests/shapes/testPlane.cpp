#include "catch.hpp"

#include "shapes/plane.h"
#include "math/tuple.h"
#include "math/transformations.h"
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

    SECTION("creating a plane with a material should work")
    {
        material m;
        m.set_color({0.8, 1.0, 0.6});
        m.set_diffuse(0.7);
        m.set_specular(0.2);
    
        plane p {m};
        REQUIRE(p.mat() == m);

        material m1;
        m1.set_diffuse(0.1);
        p.set_material(m1);
        REQUIRE(p.mat() == m1);
    }

    SECTION("plane transform should work")
    {
        plane p {};
        REQUIRE(p.transform() == matrix4x4 {});
        p.set_transform(scaling(2, 2, 2));
        REQUIRE(p.transform() == scaling(2, 2, 2));
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
