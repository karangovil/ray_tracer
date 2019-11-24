#ifndef MATERIAL_H
#define MATERIAL_H

#include "colors.h"
#include "utils.h"

namespace RT
{

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

} //end namespace RT
#endif
