#include "shapes/sphere.h"
#include "graphics/intersection.h"
#include "shapes/material.h"
#include "graphics/ray.h"
#include "graphics/world.h"

namespace RT
{

sphere::sphere()
    : m_center {point(0.0, 0.0, 0.0)},
      m_radius {1.0} {}

sphere::sphere(tuple center, num_t radius)
    : m_center {center},
      m_radius {radius} {}

sphere::sphere(material mat)
    : m_center {point(0.0, 0.0, 0.0)},
      m_radius {1.0},
      m_material {mat} {}

std::shared_ptr<object> sphere::create() const
{ return std::make_shared<sphere>(); };

std::shared_ptr<object> sphere::clone() const
{ return std::make_shared<sphere>(*this); }

num_t sphere::radius() const { return m_radius; }
tuple sphere::center() const { return m_center; }
matrix4x4 sphere::transform() const { return m_transform; }
material const& sphere::mat() const { return m_material; }

void sphere::set_transform(matrix4x4 t) { m_transform = t; }
void sphere::set_material(struct material m) { m_material = m; }

tuple sphere::normal_at(tuple world_point) const
{
    auto object_point = inverse(m_transform) * world_point;
    auto object_normal = object_point - m_center;
    auto world_normal = transpose(inverse(m_transform)) * object_normal;
    world_normal.w = 0.0;
    return normalize(world_normal);
}

opt_int_v_t sphere::intersect(ray const& r) const
{
    ray r2 = r.transform(inverse(m_transform));

    auto sphere_to_ray = r2.origin() - m_center;
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
        return std::vector<intersection> {
            intersection {static_pointer_cast<const object>(shared_from_this()), t1},
            intersection {static_pointer_cast<const object>(shared_from_this()), t2}
        };
    }
}

} //end namespace RT
