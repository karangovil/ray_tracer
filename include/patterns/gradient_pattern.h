#ifndef GRADIENT_PATTERN_H
#define GRADIENT_PATTERN_H

#include "patterns/patterns_base.h"

namespace RT
{

struct gradient_pattern : public pattern
{
public:
    gradient_pattern(color a, color b)
        : pattern {a, b} {}
    
    color pattern_at(tuple const& pt) const override
    {
        return m_a + (m_b - m_a) * (pt.x - std::floor(pt.x));
    }
};

} // end namespace RT

#endif
