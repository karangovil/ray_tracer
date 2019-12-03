#ifndef JITTER_H
#define JITTER_H

#include "math/perlin.h"
#include "math/tuple.h"

namespace RT
{

inline
tuple add_jitter(tuple const& pt)
{
    perlin& p = perlin::getInstance();
    auto noise_x = p.octaveNoise(pt.x + 0.0, pt.y, pt.z, 8);
    auto noise_y = p.octaveNoise(pt.x + 1.0, pt.y, pt.z, 8);
    auto noise_z = p.octaveNoise(pt.x + 2.0, pt.y, pt.z, 8);
    
    num_t factor = 0.2;
    return point(pt.x + factor * noise_x,
                 pt.y + factor * noise_y,
                 pt.z + factor * noise_z);
}

} // end namespace RT
#endif
