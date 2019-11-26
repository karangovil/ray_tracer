#include "catch.hpp"

#include "math/matrix4x4.h"
#include "math/tuple.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("matrix4x4 operations should work")
{
    SECTION("default initialization should work")
    {
        matrix4x4<int> m;
        REQUIRE(m(0,0) == 1);
        REQUIRE(m(1,1) == 1);
        REQUIRE(m(2,2) == 1);
        REQUIRE(m(3,3) == 1);

        m(0,0) = 3;
        REQUIRE(m(0,0) == 3);

        REQUIRE_THROWS_WITH(m.at(3,4), "matrix<T> : index is out of range");
        REQUIRE_THROWS_AS(m.at(3,4), std::out_of_range);
    }

    matrix4x4<int> m ({ 1, 2, 3, 4,
                        5, 6, 7, 8,
                        8, 7, 6, 5,
                        4, 3, 2, 1 });

    SECTION("initialization should work")
    {
        REQUIRE(m(0,0) == 1);
        REQUIRE(m(1,1) == 6);
        REQUIRE(m(2,2) == 6);
        REQUIRE(m(3,3) == 1);
    }

    SECTION("copy constructor/assn should work")
    {
        matrix4x4<int> m1 {m};
        REQUIRE(m1(0,0) == 1);
        REQUIRE(m1(1,1) == 6);
        REQUIRE(m1(2,2) == 6);
        REQUIRE(m1(3,3) == 1);
        
        matrix4x4<int> m2;
        m2 = m1;
        REQUIRE(m2(0,0) == 1);
        REQUIRE(m2(1,1) == 6);
        REQUIRE(m2(2,2) == 6);
        REQUIRE(m2(3,3) == 1);
    }

    SECTION("equality should work")
    {
        matrix4x4<int> m1 ({ 1, 2, 3, 4,
                            5, 6, 7, 8,
                            8, 7, 6, 5,
                            4, 3, 2, 1 });

        REQUIRE(m1 == m);
    }

    SECTION("matrix multiplication should work")
    {
        matrix4x4<int> m1 ({ 1, 2, 3, 4,
                            5, 6, 7, 8,
                            9, 8, 7, 6,
                            5, 4, 3, 2 });

        matrix4x4<int> m2 ({ -2, 1, 2, 3,
                            3, 2, 1, -1,
                            4, 3, 6, 5,
                            1, 2, 7, 8 });


        matrix4x4<int> m3 ({ 20, 22, 50, 48,
                            44, 54, 114, 108,
                            40, 58, 110, 102,
                            16, 26, 46, 42 });

        REQUIRE(m1 * m2 == m3);
    }
    
    SECTION("matrix/tuple multiplication should work")
    {
        matrix4x4<int> m  ({ 1, 2, 3, 4,
                             2, 4, 4, 2,
                             8, 6, 4, 1,
                             0, 0, 0, 1 });

        tuple<int> t { 1, 2, 3, 1 };

        tuple<int> res {18, 24, 33, 1 };

        REQUIRE(m * t == res);
    }
    
    SECTION("matrix/scalar multiplication should work")
    {
        int s {2};
        matrix4x4<int> m1 ({ 2, 4, 6, 8,
                             10, 12, 14, 16,
                             16, 14, 12, 10,
                             8, 6, 4, 2});
        REQUIRE(m * s == m1);
        REQUIRE(s * m == m1);
    }
    
    SECTION("matrix/scalar multiplication should work")
    {
        matrix4x4<int> m1 ({ 1, 5, 8, 4,
                             2, 6, 7, 3,
                             3, 7, 6, 2,
                             4, 8, 5, 1});
        REQUIRE(transpose(m) == m1);
    }
    
    SECTION("matrix inversion should work")
    {
        matrix4x4<int> id;

        matrix4x4<int> m ({ -5, 2, 6, -8,
                             1, -5, 1, 8,
                             7, 7, -6, -7,
                             1, -3, 7, 4 });

        REQUIRE(inverse(m) * m == id);
        REQUIRE(determinant(m) == 532);
    }
}
