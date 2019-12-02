#ifndef REFLECTION_H
#define REFLECTION_H

#include <memory>

namespace RT
{

struct world;
struct ray;
struct color;
struct tuple;
struct material;
struct point_light;
struct computations;
struct object;

// compute reflected vector
tuple reflect(tuple const& in, tuple const& normal);

// check if a point is shadowed
bool is_shadowed(world const& w, tuple const& pt);

// compute lighting of a point using Phong reflection model
color lighting(std::shared_ptr<object> const& obj,
               point_light const& l,
               tuple const& position,
               tuple const& eye_v,
               tuple const& normal_v,
               bool const in_shadow);

// compute shading intensity for hit points
color shade_hit(world const& w, computations const& c);

// compute color at a point where a ray hits an object
color color_at(world const& w, ray const& r);

} // end namespace RT
#endif
