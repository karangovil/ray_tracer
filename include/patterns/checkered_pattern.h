#ifndef CHECKERED_PATTERN_H
#define CHECKERED_PATTERN_H

#include "patterns/patterns_base.h"

namespace RT
{

struct checkered_pattern : public pattern
{
public:
    checkered_pattern(color a, color b)
        : pattern {a, b} {}
    
    color pattern_at(tuple const& pt) const override
    {
        return std::fmod((std::floor(pt.x) + std::floor(pt.y) + std::floor(pt.z)), 2) == static_cast<num_t>(0.0)
            ?  m_a : m_b;
    }
};

} // end namespace RT

#endif
