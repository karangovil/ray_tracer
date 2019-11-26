#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

#include "math/matrix4x4.h"
#include "shapes/material.h"

namespace RT
{

struct object
{
    virtual ~object() = default;

    virtual std::shared_ptr<object> create() const = 0;
    virtual std::shared_ptr<object> clone() const = 0;

    virtual matrix4x4<double> transform() const = 0;
    virtual void set_transform(matrix4x4<double> t) = 0;
    virtual material const& mat() const = 0;
    virtual void set_material(material m) = 0;
    virtual tuple<double> normal_at(tuple<double> world_point) const = 0;
};

} // end namespace RT
#endif
