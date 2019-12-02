#include "graphics/ray.h"
#include "graphics/light.h"
#include "math/tuple.h"
#include "graphics/canvas.h"
#include "graphics/intersection.h"
#include "shapes/sphere.h"
#include "shapes/object.h"
#include "math/transformations.h"
#include "graphics/reflection.h"

#include <memory>

using namespace RT;

int main()
{
    auto ray_origin = point(0.0, 0.0, -5.0);

    int wall_z = 10;

    double wall_size = 7.0;

    size_t canvas_pixels = 500;

    double pixel_size = wall_size / canvas_pixels;

    double half = wall_size / 2.0;

    color red {1, 0, 0};

    canvas c {canvas_pixels, canvas_pixels};

    std::shared_ptr<object> s = std::make_shared<sphere>();

    material m;
    m.set_color({1.0, 0.2, 1.0});
    s->set_material(m);

    auto light_position = point(-10.0, 10.0, -10.0);
    color light_color {1.0, 1.0, 1.0};
    point_light light {light_position, light_color};

    for (size_t y = 0; y < canvas_pixels; ++y)
    {
        auto world_y = half - pixel_size * y;
        for (size_t x = 0; x < canvas_pixels; ++x)
        {
            auto world_x = -half + pixel_size * x;
            auto pos = point(world_x, world_y, wall_z);
            ray r {ray_origin, normalize(pos - ray_origin)};
            auto xs = s->intersect(r);
            if (xs.has_value())
            {
                auto h = hit(xs.value());
                if (h.has_value())
                {
                    auto p = r.position(h.value().t());
                    auto normal = s->normal_at(p);
                    auto eye_v = -r.direction();
                    auto col = lighting(s, light, p, eye_v, normal, false);
                    write_pixel(c, x, y, col);
                }
            }
        }
    }

    canvas_to_ppm(c, "raySphere");

    return 0;
}
