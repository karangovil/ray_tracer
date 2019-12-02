#include "shapes/sphere.h"
#include "graphics/intersection.h"
#include "graphics/ray.h"
#include "graphics/world.h"

namespace RT
{

sphere::sphere()
    : m_center {point(0.0, 0.0, 0.0)},
      m_radius {1.0},
      m_material {material {}},
      m_transform {matrix4x4 {}} {}

sphere::sphere(tuple const& center, num_t const radius)
    : m_center {center},
      m_radius {radius},
      m_material {material {}},
      m_transform {matrix4x4 {}} {}

sphere::sphere(material const& mat)
    : m_center {point(0.0, 0.0, 0.0)},
      m_radius {1.0},
      m_material {mat},
      m_transform {matrix4x4 {}} {}

// std::shared_ptr<object> sphere::create() const
// { return std::make_shared<sphere>(); };
//
// std::shared_ptr<object> sphere::clone() const
// { return std::make_shared<sphere>(*this); }

num_t sphere::radius() const { return m_radius; }
tuple sphere::center() const { return m_center; }
matrix4x4 sphere::transform() const { return m_transform; }
material const& sphere::mat() const { return m_material; }

void sphere::set_transform(matrix4x4 const& t) { m_transform = t; }
void sphere::set_material(material const& m) { m_material = m; }

tuple sphere::local_normal_at(tuple const& local_point) const
{
    auto local_normal = local_point - m_center;
    local_normal.w = 0.0;
    return normalize(local_normal);
}

opt_int_v_t sphere::local_intersect(ray const& local_ray) const
{
    auto sphere_to_ray = local_ray.origin() - m_center;
    auto a = dot(local_ray.direction(), local_ray.direction());
    auto b = 2.0 * dot(local_ray.direction(), sphere_to_ray);
    auto c = dot(sphere_to_ray, sphere_to_ray) - 1.0;

    auto discriminant = (b * b - 4.0 * a * c);
    if (discriminant < 0)
        return std::nullopt;
    else
    {
        auto t1 = (-b - std::sqrt(discriminant)) / (2.0 * a); 
        auto t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
        return std::vector<intersection> {
            intersection {get_object_sp(), t1},
            intersection {get_object_sp(), t2}
        };
    }
}

} //end namespace RT
