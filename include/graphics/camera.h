#ifndef CAMERA_H
#define CAMERA_H

#include "math/transformations.h"

namespace RT
{

struct camera
{
public:
    camera(size_t hsize, size_t vsize, double fov)
        : m_hsize {hsize},
          m_vsize {vsize},
          m_fov {fov},
          m_transform {matrix4x4<double> {}} {}

    size_t const hsize() const { return m_hsize; }
    size_t const vsize() const { return m_vsize; }
    double const fov() const { return m_fov; }
    matrix4x4<double> const transform() const { return m_transform; }
    
    void set_hsize(size_t const h) { m_hsize = h; }
    void set_vsize(size_t const v) { m_vsize = v; }
    void set_fov(double const f) { m_fov = f; }
    void set_transform(matrix4x4<double> const& m) { m_transform = m; }
private:
    size_t m_hsize, m_vsize;
    double m_fov;
    matrix4x4<double> m_transform;
};

} // end namespace RT

#endif
