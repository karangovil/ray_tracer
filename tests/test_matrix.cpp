#include "catch.hpp"

#include "matrix.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("matrix initialization should work")
{
    SECTION("default initialization should work")
    {
       matrix<int> m(3,3);
       REQUIRE(m(0,0) == 0);

       m(0,0) = 3;
       REQUIRE(m(0,0) == 3);

      REQUIRE_THROWS_WITH(m(3,3), "matrix<T> : index is out of range");
      REQUIRE_THROWS_AS(m(3,3), std::out_of_range);
    }
}
