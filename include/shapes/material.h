#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "common.h"
#include "graphics/colors.h"
#include "patterns/patterns_base.h"

namespace RT
{

struct material
{
public:
    material();
    material(num_t amb, num_t diff, num_t spec, num_t shiny, num_t reflective, color col);

    num_t ambient() const { return m_ambient; }
    num_t diffuse() const { return m_diffuse; }
    num_t specular() const { return m_specular; }
    num_t shininess() const { return m_shininess; }
    num_t reflective() const { return m_reflective; }
    color col() const { return m_color; }
    std::shared_ptr<const pattern> get_pattern() const { return m_pattern; }

    void set_ambient(num_t amb) { m_ambient = amb; }
    void set_diffuse(num_t diff) { m_diffuse = diff; }
    void set_specular(num_t spec) { m_specular = spec; }
    void set_shininess(num_t shiny) { m_shininess = shiny; }
    void set_reflective(num_t reflective) { m_reflective = reflective; }
    void set_color(color col) { m_color = col; }
    void set_pattern(std::shared_ptr<const pattern> p) { m_pattern = p; }
private:
    num_t m_ambient;
    num_t m_diffuse;
    num_t m_specular;
    num_t m_shininess;
    num_t m_reflective;
    color m_color;
    std::shared_ptr<const pattern> m_pattern;
};

bool operator==(material const& m1, material const& m2);

} //end namespace RT
#endif
