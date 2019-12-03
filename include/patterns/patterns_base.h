#ifndef PATTERNS_BASE_H
#define PATTERNS_BASE_H

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

} // end namespace RT
#endif
