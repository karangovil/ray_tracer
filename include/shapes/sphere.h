#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "common.h"
#include "shapes/material.h"
#include "shapes/object.h"
#include "math/tuple.h"
#include "math/matrix4x4.h"

namespace RT
{

struct ray;
struct world;

struct sphere : public object
{
public:
    sphere();
    sphere(tuple center, num_t radius);
    sphere(material mat);

    // std::shared_ptr<object> create() const override;
    // std::shared_ptr<object> clone() const override;

    num_t radius() const;
    tuple center() const;
    matrix4x4 transform() const override;
    material const& mat() const override;

    void set_transform(matrix4x4 t) override;
    void set_material(struct material m) override;
private:
    tuple m_center;
    num_t m_radius;
    material m_material;
    matrix4x4 m_transform;

    tuple local_normal_at(tuple local_point) const override;
    opt_int_v_t local_intersect(ray const& local_ray) const override;
};

inline
auto operator==(sphere const& s1, sphere const& s2) -> bool
{
    return (s1.radius() == s2.radius()) &&
           (s1.center() == s2.center()) &&
           (s1.transform() == s2.transform()) &&
           (s1.mat() == s2.mat());
}

} // end namespace RT
#endif
