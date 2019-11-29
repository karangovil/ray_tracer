#include "catch.hpp"

#include "graphics/camera.h"
#include "graphics/ray.h"
#include "graphics/canvas.h"
#include "graphics/world.h"
#include "math/transformations.h"

using namespace Catch::literals;
using namespace RT;

TEST_CASE("camera should work")
{
    SECTION("camera initialization should work")
    {
        camera c {160, 120, M_PI / 2.0};
        REQUIRE(c.hsize() == 160);
        REQUIRE(c.vsize() == 120);
        REQUIRE(c.fov() == M_PI / 2.0);
        REQUIRE(c.transform() == matrix4x4 {});
    }
    
    SECTION("camera pixel_size should work")
    {
        camera c1 {200, 125, M_PI / 2.0};
        REQUIRE(Approx(c1.pixel_size()).margin(2) == 0.01);
        
        camera c2 {125, 200, M_PI / 2.0};
        REQUIRE(Approx(c2.pixel_size()).margin(2) == 0.01);
    }

    SECTION("ray_for_pixel should work 1")
    {
        camera c {201, 101, M_PI / 2.0};
        auto r = ray_for_pixel(c, 100, 50);
        REQUIRE(r.origin() == point(0.0, 0.0, 0.0));
        REQUIRE(r.direction() == vector(0.0, 0.0, -1.0));
    }
    
    SECTION("ray_for_pixel should work 2")
    {
        camera c {201, 101, M_PI / 2.0};
        auto r = ray_for_pixel(c, 0, 0);
        REQUIRE(r.origin() == point(0.0, 0.0, 0.0));
        auto expected_dir = vector(0.66519, 0.33259, -0.66851);
        REQUIRE(expected_dir.x == Approx(r.direction().x).margin(5));
        REQUIRE(expected_dir.y == Approx(r.direction().y).margin(5));
        REQUIRE(expected_dir.z == Approx(r.direction().z).margin(5));
    }
    
    SECTION("ray_for_pixel should work 3")
    {
        camera c {201, 101, M_PI / 2.0};
        c.set_transform(rotation_y(M_PI / 4.0) * translation(0.0, -2.0, 5.0));
        auto r = ray_for_pixel(c, 100, 50);
        REQUIRE(r.origin() == point(0.0, 2.0, -5.0));
        REQUIRE(r.direction() == vector(std::sqrt(2) / 2, 0.0, -std::sqrt(2) / 2));
    }

    SECTION("render should work")
    {
        world w;
        camera c {11, 11, M_PI / 2.0};
        auto from = point(0.0, 0.0, -5.0);
        auto to = point(0.0, 0.0, 0.0);
        auto up = vector(0.0, 1.0, 0.0);
        c.set_transform(view_transform(from, to, up));
        auto image = render(c, w);
        REQUIRE(pixel_at(image, 5, 5) == color {0.38066, 0.47583, 0.2855});
    }
}
