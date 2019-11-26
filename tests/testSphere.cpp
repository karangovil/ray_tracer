#include "catch.hpp"

#include "shapes/sphere.h"
#include "math/transformations.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("sphere should work")
{
    SECTION("creating a default sphere should work")
    {
        sphere s;
        REQUIRE(s.radius() == 1.0);
        REQUIRE(s.center() == point(0.0, 0.0, 0.0));
    }
    
    SECTION("creating a sphere should work")
    {
        double radius = 5.0;
        tuple<double> center {1.0, 2.0, 3.0};
        sphere s {center, radius};
        REQUIRE(s.radius() == radius);
        REQUIRE(s.center() == center);
    }
    
    SECTION("creating a sphere with a material should work")
    {
        material m;
        m.set_color({0.8, 1.0, 0.6});
        m.set_diffuse(0.7);
        m.set_specular(0.2);
    
        sphere s {m};
        REQUIRE(s.mat() == m);
    }

    SECTION("normals should work")
    {
        sphere s;
        REQUIRE(s.normal_at(point<double>(1, 0, 0)) == vector(1, 0, 0));
        REQUIRE(s.normal_at(point<double>(0, 1, 0)) == vector(0, 1, 0));
        REQUIRE(s.normal_at(point<double>(0, 0, 1)) == vector(0, 0, 1));
        
        s.set_transform(translation(0.0, 1.0, 0.0)); 
        auto n1 = s.normal_at(point(0.0, 1.70711, -0.70711)); 
        REQUIRE(n1.x == Approx(0.0));
        REQUIRE(n1.y == Approx(0.707107).margin(1e-6));
        REQUIRE(n1.z == Approx(-0.707107).margin(1e-6));
        
        s.set_transform(scaling(1.0, 0.5, 1.0) * rotation_z(M_PI / 5.0));
        auto n2 = s.normal_at(point(0.0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0));
        REQUIRE(n2.x == Approx(0.0));
        REQUIRE(n2.y == Approx(0.970143).margin(1e-6));
        REQUIRE(n2.z == Approx(-0.242536).margin(1e-6));
    }

    SECTION("sphere material should work")
    {
        sphere s;

        material m;
        REQUIRE(m == s.mat());

        m.set_ambient(1.0);
        s.set_material(m);
        REQUIRE(m == s.mat());

    }

}
