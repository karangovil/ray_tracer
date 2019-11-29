#include "graphics/ray.h"
#include "math/matrix4x4.h"

namespace RT
{

ray::ray(tuple origin, tuple direction)
        : m_origin {origin},
          m_direction {direction} {}
    
tuple ray::origin() const { return m_origin; }
tuple ray::direction() const { return m_direction; }

tuple ray::position(num_t const t) const
{ return m_origin + m_direction * t; }

ray RT::ray::transform(matrix4x4 const& m) const
{ return ray { m * m_origin, m * m_direction }; }

} //end namespace RT
