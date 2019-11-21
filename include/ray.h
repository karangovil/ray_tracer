#ifndef RAY_H
#define RAY_H

#include "tuple.h"
#include "matrix4x4.h"

namespace RT
{

template<typename Point, typename Vector>
struct ray
{
public:
    ray(tuple<Point> origin, tuple<Vector> direction)
        : m_origin {origin}, m_direction {direction} {}

    tuple<Point> origin() const { return m_origin; }
    tuple<Vector> direction() const { return m_direction; }
private:
    tuple<Point> m_origin;
    tuple<Vector> m_direction;
};

template<typename Point, typename Vector>
auto position(ray<Point, Vector> const& r, double const t)
{ return r.origin() + r.direction() * t; }

template<typename Point, typename Vector, typename T>
auto transform(ray<Point, Vector> r, matrix4x4<T> m)
{ return ray { m * r.origin(), m * r.direction() }; }

} // end namespace RT

#endif
