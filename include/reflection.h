#ifndef REFLECTION_H
#define REFLECTION_H

#include "tuple.h"
#include "colors.h"
#include "material.h"
#include "light.h"

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

} // end namespace RT
#endif
