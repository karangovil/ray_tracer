#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "tuple.h"
#include "matrix4x4.h"

namespace RT
{

struct sphere : public object
{
public:
    sphere()
        : m_center {point(0.0, 0.0, 0.0)},
          m_radius {1.0} {}

    sphere(tuple<double> center, double radius)
        : m_center {center},
          m_radius {radius} {}

    double radius() const { return m_radius; }
    tuple<double> center() const { return m_center; }
    matrix4x4<double> transform() const { return m_transform; }

    void set_transform(matrix4x4<double> t) { m_transform = t; }

private:
    tuple<double> m_center;
    double m_radius;
    matrix4x4<double> m_transform;
};

} // end namespace RT
#endif
