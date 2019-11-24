#include "catch.hpp"

#include "canvas.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("canvas should work")
{
    SECTION("creating a canvas should work")
    {
        canvas c { 10, 20 };
        REQUIRE(c.width == 10);
        REQUIRE(c.height == 20);
        REQUIRE(c.pixels == std::vector<color<float>> (10 * 20, color<float> {0.0, 0.0, 0.0}));
        REQUIRE(c.pixels[10] == color<float> {0.0, 0.0, 0.0});
    }

    SECTION("writing pixels to canvas should work")
    {
        canvas c { 10, 20 };
        color<float> red {1.0, 0.0, 0.0};

        write_pixel(c, 2, 3, red);
        REQUIRE(pixel_at(c, 2, 3) == red);
    }
    
    SECTION("writing a canvas to ppm file should work")
    {
        canvas c { 5, 3 };
        color<float> c1 {1.5, 0, 0 };
        color<float> c2 {0, 0.5, 0 };
        color<float> c3 {-0.5, 0, 1 };

        write_pixel(c, 0, 0, c1);
        write_pixel(c, 2, 1, c2);
        write_pixel(c, 4, 2, c3);

        canvas_to_ppm(c, "test_canvas");
    }
}
