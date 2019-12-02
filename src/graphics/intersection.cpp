#include "graphics/intersection.h"
#include "graphics/world.h"
#include "shapes/object.h"

#include <algorithm>

namespace RT
{

intersection::intersection(std::shared_ptr<object> const& obj, double t)
    : m_obj {obj}, m_t {t} {}

intersection::intersection(intersection const& i)
{
    m_t = i.t();
    m_obj = i.obj();
}

intersection& intersection::operator=(intersection const& i)
{
    m_t = i.t();
    m_obj = i.obj();
    return *this;
}

bool operator==(intersection const& i1, intersection const& i2)
{ return ((i1.t() == i2.t()) && (i1.obj() == i2.obj())); }

opt_int_v_t intersect_world(world const& w, ray const& r)
{
    std::vector<intersection> res;
    for (auto  const& o : w.objs())
    {
        auto ints = o->intersect(r);
        if (ints.has_value())
            res.insert(res.begin(), ints.value().begin(), ints.value().end());
    }

    if (res.size() == 0)
        return std::nullopt;
    else
    {
        std::sort(res.begin(), res.end(),
                [](auto e1, auto e2) { return e1.t() < e2.t(); });
        return res;
    }
}

std::optional<intersection> hit(std::vector<intersection> const& is) 
{
    std::vector<intersection> isPos;
    for (auto const& el : is)
    {
        if (el.t() > 0.0)
            isPos.emplace_back(el);
    }
    if (isPos.size() == 0)
        return std::nullopt;
    else
    {
        auto min = std::min_element(isPos.begin(), isPos.end(),
                    [](auto const& el1, auto const& el2)
                        { return el1.t() < el2.t(); });
        return *min;
    }
}

} // end namespace RT
