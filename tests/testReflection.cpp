#include "catch.hpp"

#include <cmath>

#include "graphics/reflection.h"
#include "graphics/intersection.h"
#include "graphics/computations.h"
#include "graphics/light.h"
#include "shapes/material.h"
#include "shapes/object.h"
#include "graphics/world.h"
#include "graphics/ray.h"
#include "graphics/colors.h"
#include "math/tuple.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("reflections should work")
{
    SECTION("reflecting a vector approaching at 45deg should work")
    {
        auto v = vector(1, -1, 0);
        auto n = vector(0, 1, 0);

        REQUIRE(reflect(v, n) == vector(1, 1, 0));
    }

    SECTION("reflecting a vector off a slanted surface should work")
    {
        auto v = vector(0.0, -1.0, 0.0);
        auto n = vector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0.0);

        REQUIRE(reflect(v, n) == vector(1, 0, 0));
    }
    
    SECTION("lighting should work")
    {
        material m;
        auto pos = point(0.0, 0.0, 0.0);
        auto eye_v = vector(0.0, 0.0, -1.0);
        auto normal_v = vector(0.0, 0.0, -1.0);
        point_light light {point(0.0, 0.0, -10.0), color {1.0, 1.0, 1.0}};

        REQUIRE(lighting(m, light, pos, eye_v, normal_v, false) == color {1.9, 1.9, 1.9});
        auto eye_v_1 = vector(0.0, std::sqrt(2) / 2, std::sqrt(2) / 2);
        REQUIRE(lighting(m, light, pos, eye_v_1, normal_v, false) == color {1.0, 1.0, 1.0});
        
        point_light light_1 {point(0.0, 10.0, -10.0), color {1.0, 1.0, 1.0}};
        REQUIRE(lighting(m, light_1, pos, eye_v_1, normal_v, false) == color {0.7364, 0.7364, 0.7364});
        
        auto eye_v_2 = vector(0.0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
        REQUIRE(lighting(m, light_1, pos, eye_v_2, normal_v, false) == color {1.6364, 1.6364, 1.6364});
        
        point_light light_2 {point(0.0, 0.0, 10.0), color {1.0, 1.0, 1.0}};
        REQUIRE(lighting(m, light_2, pos, eye_v, normal_v, false) == color {0.1, 0.1, 0.1});

        // lighting in shadow should work
        REQUIRE(lighting(m, light_1, pos, eye_v, normal_v, true) == color {0.1, 0.1, 0.1});
    }

    SECTION("is_shadowed should work")
    {
        world w;
        REQUIRE_FALSE(is_shadowed(w, point(0.0, 10.0, 0.0)));
        REQUIRE(is_shadowed(w, point(10.0, -10.0, 10.0)));
        REQUIRE_FALSE(is_shadowed(w, point(-20.0, 20.0, -20.0)));
        REQUIRE_FALSE(is_shadowed(w, point(-2.0, 2.0, -2.0)));
    }

    SECTION("shading should work")
    {
        world w;
        ray r {point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
        auto obj = *w.objs().begin();
        intersection i {obj, 4.0};
        computations c {i, r};
        REQUIRE(shade_hit(w, c) == color {0.38066, 0.47583, 0.2855});
    }
    
    SECTION("more shading should work")
    {
        world w;
        w.set_light(point_light {point(0.0, 0.25, 0.0), color {1.0, 1.0, 1.0}});
        ray r {point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0)};
        auto obj = *(std::next((w.objs().begin())));
        intersection i {obj, 0.5};
        computations c {i, r};
        REQUIRE(shade_hit(w, c) == color {0.90498, 0.90498, 0.90498});
    }

    SECTION("color_at should work")
    {
        world w;
        ray r1 {point(0.0, 0.0, -5.0), vector(0.0, 1.0, 0.0)};
        REQUIRE(color_at(w, r1) == color {0.0, 0.0, 0.0});
        
        ray r2 {point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
        REQUIRE(color_at(w, r2) == color {0.38066, 0.47583, 0.2855});

        auto inner = *(std::next((w.objs().begin())));
        auto m_inner = inner->mat();
        m_inner.set_ambient(1.0);
        inner->set_material(m_inner);
        ray r3 {point(0.0, 0.0, 0.75), vector(0.0, 0.0, -1.0)};
        REQUIRE(color_at(w, r3) == inner->mat().col());
    } 
}
