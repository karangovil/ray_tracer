#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include "common.h"
#include "math/matrix4x4.h"

namespace RT
{

struct ray;
struct world;
struct canvas;

struct camera
{
public:
    camera(size_t hsize, size_t vsize, num_t fov);

    size_t const hsize() const { return m_hsize; }
    size_t const vsize() const { return m_vsize; }
    num_t const fov() const { return m_fov; }
    num_t const pixel_size() const { return m_pixel_size; }
    num_t const half_width() const { return m_half_width; }
    num_t const half_height() const { return m_half_height; }
    matrix4x4 const transform() const { return m_transform; }
    
    void set_hsize(size_t const h) { m_hsize = h; }
    void set_vsize(size_t const v) { m_vsize = v; }
    void set_fov(num_t const f) { m_fov = f; }
    void set_transform(matrix4x4 const& m) { m_transform = m; }
private:
    size_t m_hsize, m_vsize;
    num_t m_fov;
    num_t m_half_width, m_half_height, m_pixel_size;
    matrix4x4 m_transform;
};

ray ray_for_pixel(camera const& c, size_t const px, size_t const py);

canvas render(camera const& c, world const& w);

} // end namespace RT

#endif
