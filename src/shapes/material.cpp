#include "shapes/material.h"
#include "graphics/colors.h"
#include "utils/equality.h"

namespace RT
{

material::material()
    : m_ambient {0.1}, m_diffuse {0.9}, m_specular {0.9},
      m_shininess {200.0}, m_color {1.0, 1.0, 1.0} {}

material::material(num_t amb, num_t diff, num_t spec, num_t shiny, color col)
    : m_ambient {amb}, m_diffuse {diff}, m_specular {spec},
      m_shininess {shiny}, m_color {col} {}

bool operator==(material const& m1, material const& m2)
{
return AlmostEquals(m1.ambient(), m2.ambient()) &&
       AlmostEquals(m1.diffuse(), m2.diffuse()) &&
       AlmostEquals(m1.specular(), m2.specular()) &&
       AlmostEquals(m1.shininess(), m2.shininess()) &&
       (m1.col() == m2.col());
}

} // end namespace RT
