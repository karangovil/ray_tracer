#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "shapes/object.h"
#include "shapes/material.h"
#include "math/matrix4x4.h"
#include "math/tuple.h"
#include "graphics/ray.h"

using namespace RT;

struct test_object : public object
{
public:
    test_object()
        : m_material {material {}},
          m_transform {matrix4x4 {}},
          m_saved_ray {ray {point(0, 0, 0), vector(1, 0, 0)}} {}

    std::shared_ptr<object> create() const
    { return std::make_shared<test_object>(); }

    std::shared_ptr<object> clone() const
    { return std::make_shared<test_object>(*this); }
    
    matrix4x4 transform() const { return m_transform; }
    material const& mat() const { return m_material; }
    ray const& saved_ray() const { return m_saved_ray; }

    void set_transform(matrix4x4 t) { m_transform = t; }
    void set_material(material m) { m_material = m; }
private:
    material m_material;
    matrix4x4 m_transform;
    mutable ray m_saved_ray;
    
    tuple local_normal_at(tuple lpt) const
    { return vector(lpt.x, lpt.y, lpt.z); }
    
    opt_int_v_t local_intersect(ray const& local_ray) const
    { m_saved_ray = local_ray; return std::nullopt; }
};

#endif
