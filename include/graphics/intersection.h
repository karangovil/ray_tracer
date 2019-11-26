#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <cmath>
#include <memory>
#include <vector>
#include <optional>
#include <algorithm>

#include "shapes/object.h"
#include "shapes/sphere.h"
#include "graphics/ray.h"
#include "math/tuple.h"
#include "math/matrix4x4.h"
#include "graphics/world.h"

namespace RT
{

struct intersection
{
public:
    intersection(std::shared_ptr<object> const& obj, double t)
        : m_obj {obj}, m_t {t} {}

    std::shared_ptr<object> obj() const { return m_obj; }
    double t() const { return m_t; }

    intersection& operator=(intersection const& i)
    {
        m_t = i.t();
        m_obj = i.obj();
        return *this;
    }
    
    intersection(intersection const& i)
    {
        m_t = i.t();
        m_obj = i.obj();
    }
private:
    std::shared_ptr<object> m_obj;
    double m_t;
};

inline
auto operator==(intersection const& i1, intersection const& i2) -> bool
{ return ((i1.t() == i2.t()) && (i1.obj() == i2.obj())); }

template<typename Point, typename Vector>
auto intersect(std::shared_ptr<object> const& sph, ray<Point, Vector> const& r)
        -> std::optional<std::vector<intersection>>
{
    auto r2 = transform(r, inverse(sph->transform()));

    auto sphere_to_ray = r2.origin() - (dynamic_cast<sphere&>(*sph)).center();
    auto a = dot(r2.direction(), r2.direction());
    auto b = 2.0 * dot(r2.direction(), sphere_to_ray);
    auto c = dot(sphere_to_ray, sphere_to_ray) - 1.0;

    auto discriminant = (b * b - 4.0 * a * c);
    if (discriminant < 0)
        return std::nullopt;
    else
    {
        auto t1 = (-b - std::sqrt(discriminant)) / (2.0 * a); 
        auto t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
        return std::vector<intersection> {intersection {sph, t1}, intersection {sph, t2}};
    }
}

template<typename Point, typename Vector>
auto intersect_world(world const& w, ray<Point, Vector> const& r)
        -> std::optional<std::vector<intersection>>
{
    std::vector<intersection> res;
    for (auto  const& o : w.objs())
    {
        auto ints = intersect(o, r);
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

inline
auto hit(std::vector<intersection> const& is) -> std::optional<intersection>
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
#endif
