#include "math/transformations.h"
#include "math/tuple.h"
#include "graphics/canvas.h"
#include "graphics/colors.h"

using namespace RT;

int main()
{
    constexpr size_t canvasSide = 512;
    canvas c { canvasSide, canvasSide };

    constexpr size_t radius = 3 * canvasSide / 8;

    const color<float> red { 1.0, 0.0, 0.0 };
    const auto twelve = point(0, 1, 0);
    for (int i = 0; i < 12; ++i)
    {
        auto r = rotation_z(i * M_PI / 6.0);
        auto temp = r * twelve;
        size_t x_pos = std::round(temp.x * radius + canvasSide / 2);
        size_t y_pos = std::round(temp.y * radius + canvasSide / 2);
        write_pixel(c, x_pos, y_pos, red);
    }
    canvas_to_ppm(c, "clock");
}
