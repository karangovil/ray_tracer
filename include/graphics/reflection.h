#ifndef REFLECTION_H
#define REFLECTION_H

#include "math/tuple.h"
#include "graphics/colors.h"
#include "shapes/material.h"
#include "graphics/light.h"
#include "graphics/world.h"
#include "graphics/computations.h"

namespace RT
{

template<typename T>
auto reflect(tuple<T> in, tuple<T> normal)
{ return (in - normal * 2 * dot(in, normal)); }

inline
auto lighting(material m,
              point_light l,
              tuple<double> position,
              tuple<double> eye_v,
              tuple<double> normal_v)
{
    color<float> effective_color = m.color() * l.intensity();
    auto light_v = normalize(l.position() - position);
    color<float> ambient = effective_color * m.ambient();
    float light_dot_normal = dot(light_v, normal_v);

    color<float> diffuse, specular;

    color<float> black {0.0, 0.0, 0.0};

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

inline
auto shade_hit(world w, computations c)
{
    return lighting(c.obj()->mat(),
                    w.light(),
                    c.point(), c.eye_v(), c.normal_v());
}

template<typename Point, typename Vector>
auto color_at(world w, ray<Point, Vector> r)
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
        { return color {0.0f, 0.0f, 0.0f}; }
    }
    else
    { return color {0.0f, 0.0f, 0.0f}; }
}

} // end namespace RT
#endif
