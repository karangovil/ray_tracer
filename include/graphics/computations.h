#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include <memory>

#include "graphics/intersection.h"
#include "graphics/ray.h"
#include "shapes/object.h"
#include "math/tuple.h"
#include "math/constants.h"

namespace RT
{

struct computations
{
public:
    computations(intersection i, ray<double, double> r)
        : m_t {i.t()},
          m_obj {i.obj()},
          m_point {position(r, m_t)},
          m_eye_v {-r.direction()},
          m_normal_v {m_obj->normal_at(m_point)}
    {
        if (dot(m_normal_v, m_eye_v) < 0.0)
        {
            m_inside = true;
            m_normal_v = -m_normal_v;
        }
        else
            m_inside = false;
        m_over_point = m_point + m_normal_v * TOLERANCE_F;
    }

    auto t() const { return m_t; }
    auto obj() const { return m_obj; }
    auto point() const { return m_point; }
    auto over_point() const { return m_over_point; }
    auto eye_v() const { return m_eye_v; }
    auto normal_v() const { return m_normal_v; }
    auto inside() const { return m_inside; }

private:
    double m_t;
    std::shared_ptr<object> m_obj;
    tuple<double> m_point, m_over_point, m_eye_v, m_normal_v;
    bool m_inside;
};

} // end namespace RT

#endif
