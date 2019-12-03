#ifndef UV_CHECKERED_PATTERN_H
#define UV_CHECKERED_PATTERN_H

#include "patterns/patterns_base.h"

namespace RT
{

struct uv_checkered_pattern : public pattern
{
public:
    uv_checkered_pattern(color a, color b, size_t width, size_t height)
        : pattern {a, b}, m_width {width}, m_height {height} {}

    color pattern_at(tuple const& pt) const override
    {
        auto [u, v] = spherical_map(pt);
        if (std::fmod((std::floor(u * m_width) +
                       std::floor(v * m_height)), 2) == static_cast<num_t>(0.0))
            return m_a;
        else
            return m_b;
    }
private:
    size_t m_width, m_height;

    std::pair<num_t, num_t> spherical_map(tuple const& pt) const
    {
        num_t theta = std::atan2(pt.x, pt.z);
        tuple vec = vector(pt.x, pt.y, pt.z);
        num_t radius = magnitude(vec);
        num_t phi = std::acos(pt.y / radius);
        num_t raw_u = theta / (2 * M_PI);
        num_t u = 1 - (raw_u + 0.5);
        num_t v = 1 - (phi / M_PI);
        return {u, v};
    }
};

} // end namespace RT

#endif
