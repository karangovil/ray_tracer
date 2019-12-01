#ifndef PLANE_H
#define PLANE_H

#include <memory>

#include "common.h"
#include "shapes/material.h"
#include "shapes/object.h"
#include "math/tuple.h"
#include "math/matrix4x4.h"

namespace RT
{

// only XZ plane is implemented with a normal in y direction
// as other orientations can be achieved via transformation matrices
struct plane : public object
{
public:
    plane();
    plane(material mat);

    // std::shared_ptr<object> create() const override;
    // std::shared_ptr<object> clone() const override;

    num_t radius() const;
    tuple center() const;
    matrix4x4 transform() const override;
    material const& mat() const override;

    void set_transform(matrix4x4 t) override;
    void set_material(struct material m) override;
private:
    material m_material;
    matrix4x4 m_transform;
    
    tuple local_normal_at(tuple local_point) const override;
    opt_int_v_t local_intersect(ray const& local_ray) const override;
};

inline
auto operator==(plane const& p1, plane const& p2) -> bool
{
    return (p1.transform() == p2.transform()) &&
           (p1.mat() == p2.mat());
}
} // end namespace RT
#endif
