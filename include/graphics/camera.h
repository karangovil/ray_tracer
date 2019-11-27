#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "math/transformations.h"
#include "math/matrix4x4.h"
#include "math/tuple.h"
#include "graphics/ray.h"
#include "graphics/world.h"
#include "graphics/canvas.h"
#include "graphics/reflection.h"

namespace RT
{

struct camera
{
public:
    camera(size_t hsize, size_t vsize, double fov)
        : m_hsize {hsize},
          m_vsize {vsize},
          m_fov {fov},
          m_transform {matrix4x4<double> {}}
    {
        auto half_view = std::tan(m_fov / 2.0);
        double aspect = (double)m_hsize / (double)m_vsize;
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

    size_t const hsize() const { return m_hsize; }
    size_t const vsize() const { return m_vsize; }
    double const fov() const { return m_fov; }
    double const pixel_size() const { return m_pixel_size; }
    double const half_width() const { return m_half_width; }
    double const half_height() const { return m_half_height; }
    matrix4x4<double> const transform() const { return m_transform; }
    
    void set_hsize(size_t const h) { m_hsize = h; }
    void set_vsize(size_t const v) { m_vsize = v; }
    void set_fov(double const f) { m_fov = f; }
    void set_transform(matrix4x4<double> const& m) { m_transform = m; }
private:
    size_t m_hsize, m_vsize;
    double m_fov;
    double m_half_width, m_half_height, m_pixel_size;
    matrix4x4<double> m_transform;
};

inline
auto ray_for_pixel(camera const& c, size_t const px, size_t const py)
{
    double xoffset = (px + 0.5) * c.pixel_size();
    double yoffset = (py + 0.5) * c.pixel_size();

    double world_x = c.half_width() - xoffset;
    double world_y = c.half_height() - yoffset;

    auto pixel = inverse(c.transform()) * point(world_x, world_y, -1.0);
    auto origin = inverse(c.transform()) * point(0.0, 0.0, 0.0);
    auto direction = normalize(pixel - origin);

    return ray<double, double> {origin, direction};
}

inline
auto render(camera const& c, world const& w)
{
    canvas image {c.hsize(), c.vsize()};
    for (size_t y = 0; y < c.vsize(); ++y)
    {
        for (size_t x = 0; x < c.hsize(); ++x)
        {
            auto r = ray_for_pixel(c, x, y);
            write_pixel(image, y, x, color_at(w, r));
        }
    }
    return image;
}

} // end namespace RT

#endif
