#include "shapes/object.h"
#include "math/tuple.h"
#include "math/transformations.h"
#include "graphics/ray.h"
#include "graphics/intersection.h"

namespace RT
{

tuple object::normal_at(tuple const& world_point) const
{
    tuple local_point = inverse(transform()) * world_point;
    tuple local_normal = local_normal_at(local_point);
    tuple world_normal = transpose(inverse(transform())) * local_normal;
    world_normal.w = static_cast<num_t>(0.0);
    return normalize(world_normal);
}

opt_int_v_t object::intersect(ray const& world_ray) const
{
    ray local_ray = world_ray.transform(inverse(transform()));
    return local_intersect(local_ray);
}

std::shared_ptr<const object> object::get_object_sp() const
{ return static_pointer_cast<const object>(shared_from_this()); }

} // end namespace RT
