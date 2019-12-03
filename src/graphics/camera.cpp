#include <math.h>

#include "graphics/camera.h"
#include "math/transformations.h"
#include "graphics/ray.h"
#include "graphics/world.h"
#include "graphics/canvas.h"
#include "graphics/reflection.h"

namespace RT
{

camera::camera(size_t hsize, size_t vsize, num_t fov)
        : m_hsize {hsize},
          m_vsize {vsize},
          m_fov {fov},
          m_transform {matrix4x4 {}}
{
    auto half_view = std::tan(m_fov / 2.0);
    num_t aspect = (num_t)m_hsize / (num_t)m_vsize;
    if (aspect >= 1.0)
    {
        m_half_width = half_view;
        m_half_height = half_view / aspect;
    }
    else
    {
        m_half_width = half_view * aspect;
        m_half_height = half_view;
    }
    m_pixel_size = (m_half_width * 2.0) / m_hsize;
}

ray ray_for_pixel(camera const& c, size_t const px, size_t const py)
{
    num_t xoffset = (px + 0.5) * c.pixel_size();
    num_t yoffset = (py + 0.5) * c.pixel_size();

    num_t world_x = c.half_width() - xoffset;
    num_t world_y = c.half_height() - yoffset;

    auto pixel = inverse(c.transform()) * point(world_x, world_y, -1.0);
    auto origin = inverse(c.transform()) * point(0.0, 0.0, 0.0);
    auto direction = normalize(pixel - origin);

    return ray {origin, direction};
}

canvas render(camera const& c, world const& w, bool const jitter)
{
    canvas image {c.hsize(), c.vsize()};
    for (size_t y = 0; y < c.vsize(); ++y)
    {
        for (size_t x = 0; x < c.hsize(); ++x)
        {
            auto r = ray_for_pixel(c, x, y);
            write_pixel(image, y, x, color_at(w, r, jitter));
        }
    }
    return image;
}

} // end namespace RT
