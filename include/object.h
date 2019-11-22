#ifndef OBJECT_H
#define OBJECT_H

#include "reflection.h"

namespace RT
{

struct object
{
    object() {}

    virtual ~object() {}

    virtual material mat() const = 0;
    virtual void set_material(material m) = 0;
    virtual tuple<double> normal_at(tuple<double> world_point) const = 0;
};

} // end namespace RT
#endif
