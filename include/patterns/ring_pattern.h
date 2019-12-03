#ifndef RING_PATTERN_H
#define RING_PATTERN_H

#include "patterns/patterns_base.h"

namespace RT
{

struct ring_pattern : public pattern
{
public:
    ring_pattern(color a, color b)
        : pattern {a, b} {}
    
    color pattern_at(tuple const& pt) const override
    {
        return std::fmod(std::floor(std::sqrt(pt.x * pt.x + pt.z * pt.z)), 2) == static_cast<num_t>(0.0)
            ?  m_a : m_b;
    }
};

} // end namespace RT

#endif
