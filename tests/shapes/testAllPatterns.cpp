#include "catch.hpp"

#include "shapes/patterns.h"
#include "shapes/material.h"
#include "shapes/sphere.h"
#include "graphics/light.h"
#include "graphics/reflection.h"
#include "math/transformations.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("striped patterns should work")
{
    color black {0, 0, 0};
    color white {1, 1, 1};

    striped_pattern p {white, black};

    SECTION("striped pattern construction should work")
    {
        REQUIRE(p.get_a() == white);
        REQUIRE(p.get_b() == black);
    }

    SECTION("stripe pattern should be constant in z")
    {
        REQUIRE(p.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(p.pattern_at(point(0, 0, 1)) == white);
        REQUIRE(p.pattern_at(point(0, 0, 2)) == white);
    }

    SECTION("stripe pattern should be constant in y")
    {
        REQUIRE(p.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(p.pattern_at(point(0, 1, 0)) == white);
        REQUIRE(p.pattern_at(point(0, 2, 0)) == white);
    }

    SECTION("stripe pattern should alternate in x")
    {
        REQUIRE(p.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(p.pattern_at(point(0.9, 0, 0)) == white);
        REQUIRE(p.pattern_at(point(1, 0, 0)) == black);
        REQUIRE(p.pattern_at(point(-0.1, 0, 0)) == black);
        REQUIRE(p.pattern_at(point(-1, 0, 0)) == black);
        REQUIRE(p.pattern_at(point(-1.1, 0, 0)) == white);
    }

    SECTION("lighting with pattern should work")
    {
        material m {};
        std::shared_ptr<pattern> sp = std::make_shared<striped_pattern>(p);
        m.set_pattern(sp);
        m.set_ambient(1);
        m.set_diffuse(0);
        m.set_specular(0);
        
        auto eye_v = vector(0, 0, -1);
        auto normal_v = vector(0, 0, -1);
        point_light light {point(0, 0, -10), color {1, 1, 1}};

        REQUIRE(lighting(m ,light, point(0.9, 0, 0), eye_v, normal_v, false) == white);
        REQUIRE(lighting(m ,light, point(1.1, 0, 0), eye_v, normal_v, false) == black);
    }

    SECTION("stripes with object transformation should work")
    {
        std::shared_ptr<object> s = std::make_shared<sphere>();
        s->set_transform(scaling(2, 2, 2));
        REQUIRE(p.pattern_at_object(s, point(1.5, 0, 0)) == white);
    }

    SECTION("stripes with pattern transformation should work")
    {
        std::shared_ptr<object> s = std::make_shared<sphere>();
        p.set_transform(scaling(2, 2, 2));
        REQUIRE(p.pattern_at_object(s, point(1.5, 0, 0)) == white);
    }

    SECTION("stripes with both object and pattern transformation should work")
    {
        std::shared_ptr<object> s = std::make_shared<sphere>();
        s->set_transform(scaling(2, 2, 2));
        p.set_transform(translation(0.5, 0, 0));
        REQUIRE(p.pattern_at_object(s, point(2.5, 0, 0)) == white);
    }

    SECTION("a gradient linearly interpolates between its colors")
    {
        gradient_pattern g {white, black};
        REQUIRE(g.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(g.pattern_at(point(0.25, 0, 0)) == color {0.75, 0.75, 0.75});
        REQUIRE(g.pattern_at(point(0.5, 0, 0)) == color {0.5, 0.5, 0.5});
        REQUIRE(g.pattern_at(point(0.75, 0, 0)) == color {0.25, 0.25, 0.25});
    }

    SECTION("a ring should extend in both x and z")
    {
        ring_pattern r {white, black};
        REQUIRE(r.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(r.pattern_at(point(1, 0, 0)) == black);
        REQUIRE(r.pattern_at(point(0, 0, 1)) == black);
        REQUIRE(r.pattern_at(point(0.708, 0, 0.708)) == black);
    }

    SECTION("checkers should repeat in x")
    {
        checkered_pattern c {white, black};
        REQUIRE(c.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(c.pattern_at(point(0.99, 0, 0)) == white);
        REQUIRE(c.pattern_at(point(1.01, 0, 0)) == black);

    }

    SECTION("checkers should repeat in y")
    {
        checkered_pattern c {white, black};
        REQUIRE(c.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(c.pattern_at(point(0, 0.99, 0)) == white);
        REQUIRE(c.pattern_at(point(0, 1.01, 0)) == black);

    }

    SECTION("checkers should repeat in z")
    {
        checkered_pattern c {white, black};
        REQUIRE(c.pattern_at(point(0, 0, 0)) == white);
        REQUIRE(c.pattern_at(point(0, 0, 0.99)) == white);
        REQUIRE(c.pattern_at(point(0, 0, 1.01)) == black);

    }

}
