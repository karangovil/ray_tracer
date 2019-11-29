#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"
#include "graphics/colors.h"

namespace RT
{

struct material
{
public:
    material();
    material(num_t amb, num_t diff, num_t spec, num_t shiny, color col);

    num_t ambient() const { return m_ambient; }
    num_t diffuse() const { return m_diffuse; }
    num_t specular() const { return m_specular; }
    num_t shininess() const { return m_shininess; }
    color col() const { return m_color; }

    void set_ambient(num_t amb) { m_ambient = amb; }
    void set_diffuse(num_t diff) { m_diffuse = diff; }
    void set_specular(num_t spec) { m_specular = spec; }
    void set_shininess(num_t shiny) { m_shininess = shiny; }
    void set_color(color col) { m_color = col; }
private:
    num_t m_ambient;
    num_t m_diffuse;
    num_t m_specular;
    num_t m_shininess;
    color m_color;
};

bool operator==(material const& m1, material const& m2);

} //end namespace RT
#endif
