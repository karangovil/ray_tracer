#include "catch.hpp"

#include "reflection.h"
#include <cmath>

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

    SECTION("point light source should work")
    {
        color<float> intensity {1.0, 1.0, 1.0};
        auto position = point(0.0, 0.0, 0.0);
        point_light light {position, intensity};

        REQUIRE(light.position() == position);
        REQUIRE(light.intensity() == intensity);
    }

    SECTION("lighting should work")
    {
        material m;
        auto pos = point(0.0, 0.0, 0.0);
        auto eye_v = vector(0.0, 0.0, -1.0);
        auto normal_v = vector(0.0, 0.0, -1.0);
        point_light light {point(0.0, 0.0, -10.0), color {1.0f, 1.0f, 1.0f}};

        REQUIRE(lighting(m, light, pos, eye_v, normal_v) == color {1.9, 1.9, 1.9});
        auto eye_v_1 = vector(0.0, std::sqrt(2) / 2, std::sqrt(2) / 2);
        REQUIRE(lighting(m, light, pos, eye_v_1, normal_v) == color {1.0, 1.0, 1.0});
        
        point_light light_1 {point(0.0, 10.0, -10.0), color {1.0f, 1.0f, 1.0f}};
        REQUIRE(lighting(m, light_1, pos, eye_v_1, normal_v) == color {0.7364, 0.7364, 0.7364});
        
        auto eye_v_2 = vector(0.0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
        REQUIRE(lighting(m, light_1, pos, eye_v_2, normal_v) == color {1.6364, 1.6364, 1.6364});
        
        point_light light_2 {point(0.0, 0.0, 10.0), color {1.0f, 1.0f, 1.0f}};
        REQUIRE(lighting(m, light_2, pos, eye_v, normal_v) == color {0.1, 0.1, 0.1});
    }

}
