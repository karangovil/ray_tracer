#include "graphics/world.h"
#include "shapes/material.h"
#include "math/transformations.h"
#include "shapes/sphere.h"
#include "graphics/light.h"
#include "graphics/colors.h"

namespace RT
{

world::world()
    : m_light {point_light {point(-10.0, 10.0, -10.0), color {1.0, 1.0, 1.0}}}
{
    auto s1 = std::make_shared<sphere>(material {0.1, 0.7, 0.2, 200.0,
                                                {0.8, 1.0, 0.6}});
    auto s2 = std::make_shared<sphere>();
    s2->set_transform(scaling(0.5, 0.5, 0.5));
    m_objs.emplace_back(s1);
    m_objs.emplace_back(s2);
}

void world::add_obj(std::shared_ptr<object> obj)
{ m_objs.emplace_back(obj); }

} //end namespace RT
