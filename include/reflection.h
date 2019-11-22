#ifndef REFLECTION_H
#define REFLECTION_H

#include "tuple.h"
#include "colors.h"

namespace RT
{

template<typename T>
auto reflect(tuple<T> in, tuple<T> normal)
{ return (in - normal * 2 * dot(in, normal)); }

struct point_light
{
public:
    point_light(tuple<double> pos, color<float> intensity)
        : m_position {pos}, m_intensity {intensity} {}

    tuple<double> position() const { return m_position; }
    color<float> intensity() const { return m_intensity; }
private:
    tuple<double> m_position;
    color<float> m_intensity;
};

struct material
{
public:
    material()
        : m_ambient {0.1}, m_diffuse {0.9}, m_specular {0.9},
          m_shininess {200.0}, m_color {1.0, 1.0, 1.0} {}

    material(float amb, float diff, float spec, float shiny, color<float> col)
        : m_ambient {amb}, m_diffuse {diff}, m_specular {spec},
          m_shininess {shiny}, m_color {col} {}

    float ambient() const { return m_ambient; }
    float diffuse() const { return m_diffuse; }
    float specular() const { return m_specular; }
    float shininess() const { return m_shininess; }
    RT::color<float> color() const { return m_color; }

    void set_ambient(float amb) { m_ambient = amb; }
    void set_diffuse(float diff) { m_diffuse = diff; }
    void set_specular(float spec) { m_specular = spec; }
    void set_shininess(float shiny) { m_shininess = shiny; }
    void set_color(RT::color<float> col) { m_color = col; }
private:
    float m_ambient;
    float m_diffuse;
    float m_specular;
    float m_shininess;
    RT::color<float> m_color;
};

auto operator==(material m1, material m2) -> bool
{
    return AlmostEquals(m1.ambient(), m2.ambient()) &&
           AlmostEquals(m1.diffuse(), m2.diffuse()) &&
           AlmostEquals(m1.specular(), m2.specular()) &&
           AlmostEquals(m1.shininess(), m2.shininess()) &&
           (m1.color() == m2.color());
}

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
