#include "catch.hpp"

#include "tuple.h"

using namespace Catch::literals;

TEST_CASE("points and vectors should work")
{
    SECTION("tuple with w = 1.0 is a point")
    {
        RT::tuple<float> a { 4.3, -4.2, 3.1, 1.0 };
        REQUIRE(a.x == 4.3_a);
        REQUIRE(a.y == -4.2_a);
        REQUIRE(a.z == 3.1_a);
        REQUIRE(a.w == 1.0_a);
        REQUIRE(RT::is_point(a));
        REQUIRE_FALSE(RT::is_vector(a));
    }
    
    SECTION("tuple with w = 0.0 is a vector")
    {
        RT::tuple<float> a { 4.3, -4.2, 3.1, 0.0 };
        REQUIRE(a.x == 4.3_a);
        REQUIRE(a.y == -4.2_a);
        REQUIRE(a.z == 3.1_a);
        REQUIRE(a.w == 0.0_a);
        REQUIRE_FALSE(RT::is_point(a));
        REQUIRE(RT::is_vector(a));
    }

    SECTION("point() creates tuple with w = 1.0")
    {
        auto p = RT::point(4, -4, 3);
        RT::tuple<int> tup { 4, -4, 3, 1 };
        REQUIRE(p == tup);
    }
    
    SECTION("vector() creates tuple with w = 0.0")
    {
        auto v = RT::vector(4, -4, 3);
        RT::tuple<int> tup { 4, -4, 3, 0 };
        REQUIRE(v == tup);
    }
    
    SECTION("adding tuples should work")
    {
        RT::tuple<int> t1 { 3, -2, 5, 1 };
        RT::tuple<int> t2 { -2, 3, 1, 0 };
        REQUIRE((t1 + t2) == RT::tuple<int> { 1, 1, 6, 1 });
    }

    SECTION("subtracting tuples should work")
    {
        auto p1 = RT::point(3, 2, 1);
        auto p2 = RT::point(5, 6, 7);
        REQUIRE((p1 - p2) == RT::vector(-2, -4, -6));

        auto v1 = RT::vector(5, 6, 7);
        REQUIRE((p1 - v1) == RT::point(-2, -4, -6));

        auto v2 = RT::vector(3, 2, 1);
        REQUIRE((v1 - v2) == RT::vector(2, 4, 6));
    }

    SECTION("negating a tuple should work")
    {
        auto zero = RT::vector(0, 0, 0);
        auto v = RT::vector(1, -2, 3);
        REQUIRE((zero -v) == RT::vector(-1, 2, -3));

        REQUIRE(-v == RT::vector(-1, 2, -3));
    }

    SECTION("scalar multiplication and division should work")
    {
        RT::tuple<int> a { 1, -2, 3, -4 };
        REQUIRE((3.5f * a) == RT::tuple<float> { 3.5, -7, 10.5, -14 });
        REQUIRE((a * 3.5f) == RT::tuple<float> { 3.5, -7, 10.5, -14 });
        
        REQUIRE((a / 2.0f) == RT::tuple<float> { 0.5, -1, 1.5, -2 });
    }

}
