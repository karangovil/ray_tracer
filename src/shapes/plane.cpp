#include "shapes/plane.h"
#include "graphics/intersection.h"
#include "graphics/ray.h"

namespace RT
{

const num_t EPSILON = 1e-8;

plane::plane()
    : m_material {material {}},
      m_transform {matrix4x4 {}} {}

plane::plane(material mat)
    : m_material {mat},
      m_transform {matrix4x4 {}} {}

std::shared_ptr<object> plane::create() const
{ return std::make_shared<plane>(); };

std::shared_ptr<object> plane::clone() const
{ return std::make_shared<plane>(*this); }

matrix4x4 plane::transform() const { return m_transform; }
material const& plane::mat() const { return m_material; }

void plane::set_transform(matrix4x4 t) { m_transform = t; }
void plane::set_material(struct material m) { m_material = m; }

tuple plane::local_normal_at(tuple local_point) const
{
    return vector(static_cast<num_t>(0.0),
                  static_cast<num_t>(1.0),
                  static_cast<num_t>(0.0));
}

opt_int_v_t plane::local_intersect(ray const& local_ray) const
{
    if (std::fabs(local_ray.direction().y) < EPSILON)
        return std::nullopt;
    else
    {
        num_t t = -local_ray.origin().y / local_ray.direction().y;
        return std::vector<intersection> { intersection {get_object_sp(), t} };
    }
}

} // end namespace RT
