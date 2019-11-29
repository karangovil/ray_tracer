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

namespace RT
{

tuple reflect(tuple in, tuple normal)
{ return (in - normal * 2 * dot(in, normal)); }

bool is_shadowed(world w, tuple pt)
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

color lighting(material m,
              point_light l,
              tuple position,
              tuple eye_v,
              tuple normal_v,
              bool in_shadow)
{
    color effective_color = m.col() * l.intensity();
    auto light_v = normalize(l.position() - position);
    color ambient = effective_color * m.ambient();
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
            diffuse = effective_color * m.diffuse() * light_dot_normal;
            auto reflect_v = reflect(-light_v, normal_v);
            auto reflect_dot_eye = dot(reflect_v, eye_v);
            if (reflect_dot_eye <= 0.0)
                specular = black;
            else
            {
                float factor = std::pow(reflect_dot_eye, m.shininess());
                specular = l.intensity() * m.specular() * factor;
            }
        }

        return ambient + diffuse + specular;
    }
}

color shade_hit(world w, computations c)
{
    return lighting(c.obj()->mat(),
                    w.light(),
                    c.over_point(), c.eye_v(), c.normal_v(),
                    is_shadowed(w, c.over_point()));
}

color color_at(world w, ray r)
{
    auto ints = intersect_world(w, r);
    if (ints.has_value())
    {
        auto h = hit(ints.value());
        if (h.has_value())
        {
            computations c {h.value(), r};
            return shade_hit(w, c);
        }
        else
        { return color {0.0, 0.0, 0.0}; }
    }
    else
    { return color {0.0, 0.0, 0.0}; }
}

} // end namespace RT
