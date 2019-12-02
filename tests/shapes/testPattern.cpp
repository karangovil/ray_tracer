#include "catch.hpp"

#include "testPattern.h"
#include "math/transformations.h"
#include "shapes/sphere.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("testPattern should work")
{
    SECTION("testPattern creation should work")
    {
        test_pattern p {};
        REQUIRE(p.transform() == matrix4x4 {});
        
        p.set_transform(translation(1, 2, 3));
        REQUIRE(p.transform() == translation(1, 2, 3));
    }

    SECTION("testPattern with object transformation should work")
    {
        test_pattern p {};
        std::shared_ptr<object> s = std::make_shared<sphere>();
        s->set_transform(scaling(2, 2, 2));

        REQUIRE(p.pattern_at_object(s, point(2, 3, 4)) == color {1, 1.5, 2});
    }

    SECTION("testPattern with pattern transformation should work")
    {
        test_pattern p {};
        std::shared_ptr<object> s = std::make_shared<sphere>();
        p.set_transform(scaling(2, 2, 2));

        REQUIRE(p.pattern_at_object(s, point(2, 3, 4)) == color {1, 1.5, 2});
    }

    SECTION("testPattern with both object and pattern transformation should work")
    {
        test_pattern p {};
        std::shared_ptr<object> s = std::make_shared<sphere>();
        s->set_transform(scaling(2, 2, 2));
        p.set_transform(translation(0.5, 1, 1.5));

        REQUIRE(p.pattern_at_object(s, point(2.5, 3, 3.5)) == color {0.75, 0.5, 0.25});
    }

}
