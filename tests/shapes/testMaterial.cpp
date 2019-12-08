#include "catch.hpp"

#include "shapes/material.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("material should work")
{
    SECTION("material default construction should work")
    {
        material m;
        REQUIRE(m.ambient() == 0.1);
        REQUIRE(m.diffuse() == 0.9);
        REQUIRE(m.specular() == 0.9);
        REQUIRE(m.shininess() == 200.0);
        REQUIRE(m.col() == color {1.0, 1.0, 1.0});
    }

    SECTION("material setters should work")
    {
        material m;
        m.set_ambient(0.2);
        m.set_diffuse(0.8);
        m.set_specular(0.8);
        m.set_shininess(180.0);
        m.set_reflective(0.5);
        m.set_color({0.9, 0.9, 0.9});

        REQUIRE(m.ambient() == 0.2);
        REQUIRE(m.diffuse() == 0.8);
        REQUIRE(m.specular() == 0.8);
        REQUIRE(m.shininess() == 180.0);
        REQUIRE(m.reflective() == 0.5);
        REQUIRE(m.col() == color {0.9, 0.9, 0.9});
    }
    
    SECTION("material construction should work")
    {
        material m {0.2, 0.8, 0.8, 180, 0.5, {0.9, 0.9, 0.9}};
        REQUIRE(m.ambient() == 0.2);
        REQUIRE(m.diffuse() == 0.8);
        REQUIRE(m.specular() == 0.8);
        REQUIRE(m.shininess() == 180.0);
        REQUIRE(m.reflective() == 0.5);
        REQUIRE(m.col() == color {0.9, 0.9, 0.9});
    }

    SECTION("material comparison should work")
    {
        material m1;
        material m2 {0.1, 0.9, 0.9, 200.0, 0.0, {1.0, 1.0, 1.0}};
        REQUIRE(m1 == m2);
    }

}
