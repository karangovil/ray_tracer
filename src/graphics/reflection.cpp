#include <math.h>

#include "graphics/reflection.h"
#include "graphics/intersection.h"
#include "graphics/computations.h"
#include "graphics/light.h"
#include "shapes/material.h"
#include "shapes/object.h"
#include "graphics/world.h"
#include "graphics/ray.h"
#include "graphics/colors.h"
#include "math/tuple.h"
#include "patterns/jitter.h"

namespace RT
{

tuple reflect(tuple const& in, tuple const& normal)
{ return (in - normal * 2 * dot(in, normal)); }

bool is_shadowed(world const& w, tuple const& pt)
{
    auto v = w.light().position() - pt;
    auto distance = magnitude(v);
    auto direction = normalize(v);

    auto is_shadowed_res = false;

    ray r {pt, direction};
    auto ints = intersect_world(w, r);
    if (ints.has_value())
    {
        auto h = hit(ints.value());
        if (h.has_value() && h.value().t() < distance)
            is_shadowed_res = true;
    }
    return is_shadowed_res;
}

color lighting(std::shared_ptr<object> const& obj,
               point_light const& l,
               tuple const& position,
               tuple const& eye_v,
               tuple const& normal_v,
               bool const in_shadow,
               bool const jitter)
{
    color m_col;
    if (obj->mat().get_pattern() != nullptr)
        m_col = obj->mat().get_pattern()->pattern_at_object(obj, jitter ?add_jitter(position) : position);
    else
        m_col = obj->mat().col();
    color effective_color = m_col * l.intensity();
    auto light_v = normalize(l.position() - position);
    color ambient = effective_color * obj->mat().ambient();
    if (in_shadow)
    { return ambient; }
    else
    {
        float light_dot_normal = dot(light_v, normal_v);

        color diffuse, specular;

        color black {0.0, 0.0, 0.0};

        if (light_dot_normal < 0.0)
        {
            diffuse = black;
            specular = black;
        }
        else
        {
            diffuse = effective_color * obj->mat().diffuse() * light_dot_normal;
            auto reflect_v = reflect(-light_v, normal_v);
            auto reflect_dot_eye = dot(reflect_v, eye_v);
            if (reflect_dot_eye <= 0.0)
                specular = black;
            else
            {
                float factor = std::pow(reflect_dot_eye, obj->mat().shininess());
                specular = l.intensity() * obj->mat().specular() * factor;
            }
        }

        return ambient + diffuse + specular;
    }
}

color shade_hit(world const& w, computations const& c, bool const jitter)
{
    return lighting(c.obj(),
                    w.light(),
                    c.over_point(), c.eye_v(), c.normal_v(),
                    is_shadowed(w, c.over_point()),
                    jitter);
}

color color_at(world const& w, ray const& r, bool const jitter)
{
    auto ints = intersect_world(w, r);
    if (ints.has_value())
    {
        auto h = hit(ints.value());
        if (h.has_value())
        {
            computations c {h.value(), r};
            return shade_hit(w, c, jitter);
        }
    }
    return color {0.0, 0.0, 0.0};
}

} // end namespace RT
