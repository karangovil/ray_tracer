#ifndef RAY_H
#define RAY_H

#include "common.h"
#include "math/tuple.h"

namespace RT
{

struct matrix4x4;

struct ray
{
public:
    ray(tuple origin, tuple direction);

    tuple origin() const;
    tuple direction() const;
    tuple position(num_t const t) const;
    ray transform(matrix4x4 const& m) const;
private:
    tuple m_origin;
    tuple m_direction;
};

} // end namespace RT

#endif
