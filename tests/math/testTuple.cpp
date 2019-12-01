#include "catch.hpp"

#include "math/tuple.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("points and vectors should work")
{
    SECTION("tuple with w = 1.0 is a point")
    {
        tuple a { 4.3, -4.2, 3.1, 1.0 };
        REQUIRE(a.x == 4.3_a);
        REQUIRE(a.y == -4.2_a);
        REQUIRE(a.z == 3.1_a);
        REQUIRE(a.w == 1.0_a);
        REQUIRE(is_point(a));
        REQUIRE_FALSE(is_vector(a));
    }
    
    SECTION("tuple with w = 0.0 is a vector")
    {
        tuple a { 4.3, -4.2, 3.1, 0.0 };
        REQUIRE(a.x == 4.3_a);
        REQUIRE(a.y == -4.2_a);
        REQUIRE(a.z == 3.1_a);
        REQUIRE(a.w == 0.0_a);
        REQUIRE_FALSE(is_point(a));
        REQUIRE(is_vector(a));
    }

    SECTION("point() creates tuple with w = 1.0")
    {
        auto p = point(4, -4, 3);
        tuple tup { 4, -4, 3, 1 };
        REQUIRE(p == tup);
    }
    
    SECTION("vector() creates tuple with w = 0.0")
    {
        auto v = vector(4, -4, 3);
        tuple tup { 4, -4, 3, 0 };
        REQUIRE(v == tup);
    }
    
    SECTION("adding tuples should work")
    {
        tuple t1 { 3, -2, 5, 1 };
        tuple t2 { -2, 3, 1, 0 };
        REQUIRE((t1 + t2) == tuple { 1, 1, 6, 1 });
    }

    SECTION("subtracting tuples should work")
    {
        auto p1 = point(3, 2, 1);
        auto p2 = point(5, 6, 7);
        REQUIRE((p1 - p2) == vector(-2, -4, -6));

        auto v1 = vector(5, 6, 7);
        REQUIRE((p1 - v1) == point(-2, -4, -6));

        auto v2 = vector(3, 2, 1);
        REQUIRE((v1 - v2) == vector(2, 4, 6));
    }

    SECTION("negating a tuple should work")
    {
        auto zero = vector(0, 0, 0);
        auto v = vector(1, -2, 3);
        REQUIRE((zero - v) == vector(-1, 2, -3));

        REQUIRE(-v == vector(-1, 2, -3));
    }

    SECTION("scalar multiplication and division should work")
    {
        tuple a { 1, -2, 3, -4 };
        REQUIRE((3.5f * a) == tuple { 3.5, -7, 10.5, -14 });
        REQUIRE((a * 3.5f) == tuple { 3.5, -7, 10.5, -14 });
        
        REQUIRE((a / 2.0f) == tuple { 0.5, -1, 1.5, -2 });
    }

    SECTION("magnitude should work")
    {
        REQUIRE(magnitude(vector(1, 0, 0)) == 1.0_a);
        REQUIRE(magnitude(vector(0, 1, 0)) == 1.0_a);
        REQUIRE(magnitude(vector(0, 0, 1)) == 1.0_a);
        REQUIRE(magnitude(vector(1, 2, 3)) == Approx(sqrt(14)));
        REQUIRE(magnitude(vector(-1, -2, -3)) == Approx(sqrt(14)));
    }

    SECTION("normalization should work")
    {
        REQUIRE(normalize(vector(4, 0, 0)) == vector(1, 0, 0));
        REQUIRE(normalize(vector(1, 2, 3)) == vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
        REQUIRE(magnitude(normalize(vector(1, 2, 3))) == 1.0_a);
    }

    SECTION("dot product should work")
    {
        auto a = vector(1, 2, 3);
        auto b = vector(2, 3, 4);
        REQUIRE(dot(a, b) == 20);
    }

    SECTION("cross product should work")
    {
        auto a = vector(1, 2, 3);
        auto b = vector(2, 3, 4);
        REQUIRE(cross(a, b) == vector(-1, 2, -1));
        REQUIRE(cross(b, a) == vector(1, -2, 1));
    }
}
