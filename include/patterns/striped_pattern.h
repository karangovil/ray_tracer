#ifndef STRIPED_PATTERN_H
#define STRIPED_PATTERN_H

#include "patterns/patterns_base.h"

namespace RT
{

struct striped_pattern : public pattern
{
public:
    striped_pattern(color a, color b)
        : pattern {a, b} {}
    
    color pattern_at(tuple const& pt) const override
    {
        return std::fmod(std::floor(pt.x), 2) == static_cast<num_t>(0.0)
            ?  m_a : m_b;
    }
};

} // end namespace RT

#endif
