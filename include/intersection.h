#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <cmath>
#include <memory>
#include <vector>
#include <optional>
#include <algorithm>

#include "object.h"
#include "sphere.h"
#include "ray.h"
#include "tuple.h"
#include "matrix4x4.h"

namespace RT
{

struct intersection
{
public:
    intersection(std::shared_ptr<object> const& obj, double t)
        : m_obj {obj}, m_t {t} {}

    std::shared_ptr<object> obj() const { return m_obj; }
    double t() const { return m_t; }

private:
    const std::shared_ptr<object> m_obj;
    const double m_t;
};

auto operator==(intersection const& i1, intersection const& i2) -> bool
{ return ((i1.t() == i2.t()) && (i1.obj() == i2.obj())); }

template<typename Point, typename Vector>
auto intersect(std::shared_ptr<object> const& sph, ray<Point, Vector> const& r)
        -> std::optional<std::vector<intersection>>
{
    auto r2 = transform(r, inverse((dynamic_cast<sphere&>(*sph)).transform()));

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
