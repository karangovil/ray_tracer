#include "catch.hpp"

#include "material.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("material should work")
{
    SECTION("material default construction should work")
    {
        material m;
        REQUIRE(m.ambient() == 0.1f);
        REQUIRE(m.diffuse() == 0.9f);
        REQUIRE(m.specular() == 0.9f);
        REQUIRE(m.shininess() == 200.0f);
        REQUIRE(m.color() == color {1.0f, 1.0f, 1.0f});
    }

    SECTION("material setters should work")
    {
        material m;
        m.set_ambient(0.2);
        m.set_diffuse(0.8);
        m.set_specular(0.8);
        m.set_shininess(180.0);
        m.set_color({0.9f, 0.9f, 0.9f});

        REQUIRE(m.ambient() == 0.2f);
        REQUIRE(m.diffuse() == 0.8f);
        REQUIRE(m.specular() == 0.8f);
        REQUIRE(m.shininess() == 180.0f);
        REQUIRE(m.color() == color {0.9f, 0.9f, 0.9f});
    }
    
    SECTION("material construction should work")
    {
        material m {0.2, 0.8, 0.8, 180, {0.9f, 0.9f, 0.9f}};
        REQUIRE(m.ambient() == 0.2f);
        REQUIRE(m.diffuse() == 0.8f);
        REQUIRE(m.specular() == 0.8f);
        REQUIRE(m.shininess() == 180.0f);
        REQUIRE(m.color() == color {0.9f, 0.9f, 0.9f});
    }

    SECTION("material comparison should work")
    {
        material m1;
        material m2 {0.1, 0.9, 0.9, 200.0, {1.0f, 1.0f, 1.0f}};
        REQUIRE(m1 == m2);
    }

}
