#include "catch.hpp"

#include "sphere.h"
#include "transformations.h"

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

    SECTION("normals should work")
    {
        sphere s;
        REQUIRE(s.normal_at(point<double>(1, 0, 0)) == vector(1, 0, 0));
        REQUIRE(s.normal_at(point<double>(0, 1, 0)) == vector(0, 1, 0));
        REQUIRE(s.normal_at(point<double>(0, 0, 1)) == vector(0, 0, 1));
        
        s.set_transform(translation(0.0, 1.0, 0.0));
        REQUIRE(s.normal_at(point(0.0, 1.70711, -0.70711)) == vector(0.0, 0.70711, -0.70711));
        
        s.set_transform(scaling(1.0, 0.5, 1.0) * rotation_z(M_PI / 5.0));
        REQUIRE(s.normal_at(point(0.0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0)) == vector(0.0, 0.970143, -0.242536));
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
