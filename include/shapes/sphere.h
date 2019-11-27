#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "shapes/material.h"
#include "shapes/object.h"
#include "math/tuple.h"
#include "math/matrix4x4.h"

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
    
    sphere(material mat)
        : m_center {point(0.0, 0.0, 0.0)},
          m_radius {1.0},
          m_material {mat} {}

    std::shared_ptr<object> create() const
    { return std::make_shared<sphere>(); };

    std::shared_ptr<object> clone() const
    { return std::make_shared<sphere>(*this); }

    double radius() const { return m_radius; }
    tuple<double> center() const { return m_center; }
    matrix4x4<double> transform() const { return m_transform; }
    material const& mat() const { return m_material; }

    void set_transform(matrix4x4<double> t) { m_transform = t; }
    void set_material(struct material m) { m_material = m; }

    tuple<double> normal_at(tuple<double> world_point) const
    {
        auto object_point = inverse(m_transform) * world_point;
        auto object_normal = object_point - m_center;
        auto world_normal = transpose(inverse(m_transform)) * object_normal;
        world_normal.w = 0.0;
        return normalize(world_normal);
    }

private:
    tuple<double> m_center;
    double m_radius;
    matrix4x4<double> m_transform;
    struct material m_material;
};

auto operator==(sphere const& s1, sphere const& s2) -> bool
{
    return (s1.radius() == s2.radius()) &&
           (s1.center() == s2.center()) &&
           (s1.transform() == s2.transform()) &&
           (s1.mat() == s2.mat());
}

} // end namespace RT
#endif
