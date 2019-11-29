#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include "graphics/light.h"

namespace RT
{

struct object;

struct world
{
public:
    world();

    point_light const& light() const { return m_light; }
    auto const& objs() const { return m_objs; }

    void set_light(point_light light) { m_light = light; }
    void add_obj(std::shared_ptr<object> obj);
    void set_objs(std::vector<std::shared_ptr<object>> objs) { m_objs = objs; }
private:
    point_light m_light; 
    std::vector<std::shared_ptr<object>> m_objs;
};

} // end namespace RT

#endif
