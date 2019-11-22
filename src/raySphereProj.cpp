#include "ray.h"
#include "tuple.h"
#include "canvas.h"
#include "intersection.h"
#include "sphere.h"
#include "object.h"
#include "transformations.h"
#include "reflection.h"

#include <memory>

using namespace RT;

int main()
{
    auto ray_origin = point(0, 0, -5);

    int wall_z = 10;

    double wall_size = 7.0;

    size_t canvas_pixels = 500;

    double pixel_size = wall_size / canvas_pixels;

    double half = wall_size / 2.0;

    color<float> red {1, 0, 0};

    canvas c {canvas_pixels, canvas_pixels};

    std::shared_ptr<object> s = std::make_shared<sphere>();

    material m;
    m.set_color({1.0, 0.2, 1.0});
    s->set_material(m);

    auto light_position = point(-10.0, 10.0, -10.0);
    color light_color {1.0f, 1.0f, 1.0f};
    point_light light {light_position, light_color};

    for (size_t y = 0; y < canvas_pixels; ++y)
    {
        auto world_y = half - pixel_size * y;
        for (size_t x = 0; x < canvas_pixels; ++x)
        {
            auto world_x = -half + pixel_size * x;
            auto pos = point<double>(world_x, world_y, wall_z);
            ray<int, double> r {ray_origin, normalize(pos - ray_origin)};
            auto xs = intersect(s, r);
            if (xs.has_value())
            {
                auto h = hit(xs.value());
                if (h.has_value())
                {
                    auto p = position(r, h.value().t());
                    auto normal = s->normal_at(p);
                    auto eye_v = -r.direction();
                    auto col = lighting(s->mat(), light, p, eye_v, normal);
                    write_pixel(c, x, y, col);
                }
            }
        }
    }

    canvas_to_ppm(c, "raySphere");

    return 0;
}
