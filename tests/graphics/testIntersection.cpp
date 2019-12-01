#include "catch.hpp"

#include "graphics/intersection.h"
#include "graphics/ray.h"
#include "math/transformations.h"
#include "shapes/sphere.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("intersections should work")
{
    SECTION("ray/sphere intersections from behind should work")
    {
        ray r {point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};

        std::shared_ptr<object> s = std::make_shared<sphere>();

        auto xs = s->intersect(r);

        REQUIRE(xs.has_value());
        REQUIRE(xs.value().size() == 2);
        REQUIRE(xs.value()[0].t() == 4.0);
        REQUIRE(xs.value()[1].t() == 6.0);
        REQUIRE(xs.value()[1].obj() == s);
        REQUIRE(xs.value()[1].obj() == s);
    }

    SECTION("tangential ray/sphere intersections should work")
    {
        ray r {point(0.0, 1.0, -5.0), vector(0.0, 0.0, 1.0)};

        std::shared_ptr<object> s = std::make_shared<sphere>();

        auto xs = s->intersect(r);

        REQUIRE(xs.has_value());
        REQUIRE(xs.value().size() == 2);
        REQUIRE(xs.value()[0].t() == 5.0);
        REQUIRE(xs.value()[1].t() == 5.0);
    }
    
    SECTION("non intersecting ray/sphere intersections should work")
    {
        ray r {point(0.0, 2.0, -5.0), vector(0.0, 0.0, 1.0)};

        std::shared_ptr<object> s = std::make_shared<sphere>();

        auto xs = s->intersect(r);

        REQUIRE_FALSE(xs.has_value());
    }

    SECTION("ray/sphere intersections from inside should work")
    {
        ray r {point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0)};

        std::shared_ptr<object> s = std::make_shared<sphere>();

        auto xs = s->intersect(r);

        REQUIRE(xs.has_value());
        REQUIRE(xs.value().size() == 2);
        REQUIRE(xs.value()[0].t() == -1.0);
        REQUIRE(xs.value()[1].t() == 1.0);
    }

    SECTION("ray/sphere intersections from front should work")
    {
        ray r {point(0.0, 0.0, 5.0), vector(0.0, 0.0, 1.0)};

        std::shared_ptr<object> s = std::make_shared<sphere>();

        auto xs = s->intersect(r);

        REQUIRE(xs.has_value());
        REQUIRE(xs.value().size() == 2);
        REQUIRE(xs.value()[0].t() == -6.0);
        REQUIRE(xs.value()[1].t() == -4.0);
    }

    SECTION("ray/sphere intersections with transforms should work")
    {
        ray r {point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};

        std::shared_ptr<object> s = std::make_shared<sphere>();
        s->set_transform(scaling(2.0, 2.0, 2.0));

        auto xs = s->intersect(r);

        REQUIRE(xs.has_value());
        REQUIRE(xs.value().size() == 2);
        REQUIRE(xs.value()[0].t() == 3.0);
        REQUIRE(xs.value()[1].t() == 7.0);
        
        s->set_transform(translation(5.0, 0.0, 0.0));
        xs = s->intersect(r);

        REQUIRE_FALSE(xs.has_value());
    }

    SECTION("hit function should work")
    {
        std::shared_ptr<object> s = std::make_shared<sphere>();
        intersection i1 {s, 1.0};
        intersection i2 {s, 2.0};

        std::vector<intersection> is {i1, i2};
        REQUIRE(hit(is) == i1);
        
        intersection i3 {s, -1.0};

        std::vector<intersection> is2 {i3, i1};
        REQUIRE(hit(is2).has_value());
        
        intersection i4 {s, -2.0};
        std::vector<intersection> is3 {i3, i4};
        REQUIRE_FALSE(hit(is3).has_value());
    }

    SECTION("hit function should work on multiple instersections")
    {
        std::shared_ptr<object> s = std::make_shared<sphere>();
        intersection i1 {s, 5.0};
        intersection i2 {s, 7.0};
        intersection i3 {s, -3.0};
        intersection i4 {s, 2.0};

        std::vector<intersection> is {i1, i2, i3, i4};
        REQUIRE(hit(is) == i4);
    }

}
