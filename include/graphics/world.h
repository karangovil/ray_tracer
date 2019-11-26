#ifndef WORLD_H
#define WORLD_H

#include <set>
#include <memory>

#include "shapes/material.h"
#include "math/transformations.h"
#include "shapes/object.h"
#include "shapes/sphere.h"
#include "graphics/light.h"
#include "graphics/colors.h"

namespace RT
{

struct world
{
public:
    world()
        : m_light {point_light {point(-10.0, 10.0, -10.0), color {1.0f, 1.0f, 1.0f}}}
   {
        auto s1 = std::make_shared<sphere> (material {0.1, 0.7, 0.2, 200.0, 
                                                      {0.8f, 1.0f, 0.6f}});
        auto s2 = std::make_shared<sphere>();
        s2->set_transform(scaling(0.5, 0.5, 0.5));
        m_objs.emplace(s1);
        m_objs.emplace(s2);
    }

    point_light light() const { return m_light; }
    auto objs() const { return m_objs; }

    void set_light(point_light light) { m_light = light; }
    void add_obj(std::shared_ptr<object> obj) { m_objs.emplace(obj); }
private:
    point_light m_light; 
    std::multiset<std::shared_ptr<object>> m_objs;
};

} // end namespace RT

#endif
