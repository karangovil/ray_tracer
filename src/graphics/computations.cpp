#include "graphics/computations.h"
#include "graphics/intersection.h"
#include "graphics/ray.h"
#include "shapes/object.h"

namespace RT
{

computations::computations(intersection i, ray r)
        : m_t {i.t()},
          m_obj {i.obj()},
          m_point {r.position(m_t)},
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

} // end namespace RT
