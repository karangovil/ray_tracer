#include "catch.hpp"

#include "math/transformations.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("matrix transformations should work")
{
    SECTION("translations should work")
    {
        auto transform = translation(5, -3, 2);

        REQUIRE(transform * point(-3, 4, 5) == point(2, 1, 7));
        REQUIRE(transform * vector(-3, 4, 5) == vector(-3, 4, 5));
        REQUIRE(inverse(transform) * point(-3, 4, 5) == point(-8, 7, 3));
    }
    
    SECTION("scaling should work")
    {
        auto transform = scaling(2, 3, 4);

        REQUIRE(transform * point(-4, 6, 8) == point(-8, 18, 32));
        REQUIRE(transform * vector(-4, 6, 8) == vector(-8, 18, 32));
        REQUIRE(inverse(transform) * point(-4, 6, 8) == point(-2, 2, 2));
        REQUIRE(scaling(-1, 1, 1) * point(2, 3, 4) == point(-2, 3, 4));
    }

    SECTION("rotation_x should work")
    {
        auto half_quarter = rotation_x(M_PI / 4.0);
        auto full_quarter = rotation_x(M_PI / 2.0);

        auto p = point(0, 1, 0);

        REQUIRE(half_quarter * p == point(0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
        REQUIRE(full_quarter * p == point(0, 0, 1));
    }

    SECTION("rotation_y should work")
    {
        auto half_quarter = rotation_y(M_PI / 4.0);
        auto full_quarter = rotation_y(M_PI / 2.0);

        auto p = point(0, 0, 1);

        REQUIRE(half_quarter * p == point(sqrt(2.0) / 2.0, 0.0, sqrt(2.0) / 2.0));
        REQUIRE(full_quarter * p == point(1, 0, 0));
    }

    SECTION("rotation_z should work")
    {
        auto half_quarter = rotation_z(M_PI / 4.0);
        auto full_quarter = rotation_z(M_PI / 2.0);

        auto p = point(0, 1, 0);

        REQUIRE(half_quarter * p == point(-sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0.0));
        REQUIRE(full_quarter * p == point(-1, 0, 0));
    }

    SECTION("shearing should work")
    {
        auto p = point(2, 3, 4);

        REQUIRE(shearing(1, 0, 0, 0, 0, 0) * p == point(5, 3, 4));
        REQUIRE(shearing(0, 1, 0, 0, 0, 0) * p == point(6, 3, 4));
        REQUIRE(shearing(0, 0, 1, 0, 0, 0) * p == point(2, 5, 4));
        REQUIRE(shearing(0, 0, 0, 1, 0, 0) * p == point(2, 7, 4));
        REQUIRE(shearing(0, 0, 0, 0, 1, 0) * p == point(2, 3, 6));
        REQUIRE(shearing(0, 0, 0, 0, 0, 1) * p == point(2, 3, 7));
    }

    SECTION("chaining transformations should work")
    {
        auto p1 = point(1, 0, 1);
        auto p2 = point(1, -1, 0);
        auto p3 = point(5, -5, 0);
        auto p4 = point(15, 0, 7);

        auto A = rotation_x(M_PI / 2.0);
        auto B = scaling(5, 5, 5);
        auto C = translation(10, 5, 7);

        REQUIRE(A * p1 == p2);
        REQUIRE(B * p2 == p3);
        REQUIRE(C * p3 == p4);
        REQUIRE(C * B * A * p1 == p4);

    }

    SECTION("identity view transform should work")
    {
        auto from = point(0.0, 0.0, 0.0);
        auto to = point(0.0, 0.0, -1.0);
        auto up = vector(0.0, 1.0, 0.0);
        REQUIRE(view_transform(from, to, up) == matrix4x4 {});
    }
    
    SECTION("reflection view transform should work")
    {
        auto from = point(0.0, 0.0, 0.0);
        auto to = point(0.0, 0.0, 1.0);
        auto up = vector(0.0, 1.0, 0.0);
        REQUIRE(view_transform(from, to, up) == scaling(-1.0, 1.0, -1.0));
    }

    SECTION("translation view transform should work")
    {
        auto from = point(0.0, 0.0, 8.0);
        auto to = point(0.0, 0.0, 0.0);
        auto up = vector(0.0, 1.0, 0.0);
        REQUIRE(view_transform(from, to, up) == translation(0.0, 0.0, -8.0));
    }

    SECTION("arbitrary view transform should work")
    {
        auto from = point(1.0, 3.0, 2.0);
        auto to = point(4.0, -2.0, 8.0);
        auto up = vector(1.0, 1.0, 0.0);

        matrix4x4 expected;

        expected(0,0) = -0.507093;
        expected(0,1) = 0.507093;
        expected(0,2) = 0.676123;
        expected(0,3) = -2.36643;

        expected(1,0) = 0.767716;
        expected(1,1) = 0.606092;
        expected(1,2) = 0.121218;
        expected(1,2) = -2.82843;

        expected(2,0) = -0.358569;
        expected(2,1) = -0.597614;
        expected(2,2) = -0.717137;

        auto res = view_transform(from, to, up);
        for (int i = 0; i < 4; ++i){
            for (int j = 0; j < 4; ++j){
                REQUIRE(expected(i,j) == Approx(res(i,j)).margin(5));
            }
        }
    }

}
