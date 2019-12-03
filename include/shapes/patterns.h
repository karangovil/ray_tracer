#ifndef PATTERNS_H
#define PATTERNS_H

#include <memory>
#include <math.h>

#include "common.h"
#include "math/matrix4x4.h"
#include "graphics/colors.h"
#include "math/tuple.h"
#include "shapes/object.h"
#include "math/perlin.h"

namespace RT
{

struct tuple;
struct object;

struct pattern : public std::enable_shared_from_this<pattern>
{
public:
    virtual ~pattern() = default;

    virtual matrix4x4 transform() const { return m_transform; }
    virtual void set_transform(matrix4x4 const& m) { m_transform = m; }

    virtual color get_a() const { return m_a; }
    virtual color get_b() const { return m_b; }

    virtual void set_a(color const& c) { m_a = c; }
    virtual void set_b(color const& c) { m_b = c; }

    virtual color pattern_at_object(std::shared_ptr<object> const& o,
                                    tuple const& world_point) const
    {
        auto object_point = inverse(o->transform()) * world_point;
        auto pattern_point = inverse(transform()) * object_point;

        return pattern_at(pattern_point);
    }

    std::shared_ptr<const pattern> get_pattern_sp() const
    { return static_pointer_cast<const pattern>(shared_from_this()); }

    virtual color pattern_at(tuple const& pt) const = 0;
protected:
    pattern(color a, color b)
        : m_a {a}, m_b {b}, m_transform {matrix4x4 {}} {}

    color m_a, m_b;
    matrix4x4 m_transform;
};


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

inline
tuple add_jitter(tuple const& pt)
{
    perlin& p = perlin::getInstance();
    auto noise_x = p.octaveNoise(pt.x + 0.0, pt.y, pt.z, 8);
    auto noise_y = p.octaveNoise(pt.x + 1.0, pt.y, pt.z, 8);
    auto noise_z = p.octaveNoise(pt.x + 2.0, pt.y, pt.z, 8);
    
    num_t factor = 0.2;
    return tuple {pt.x + factor * noise_x,
                  pt.y + factor * noise_y,
                  pt.z + factor * noise_z};
}

} // end namespace RT
#endif
