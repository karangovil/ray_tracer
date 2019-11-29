#ifndef REFLECTION_H
#define REFLECTION_H

namespace RT
{

struct world;
struct ray;
struct color;
struct tuple;
struct material;
struct point_light;
struct computations;

// compute reflected vector
tuple reflect(tuple in, tuple normal);

// check if a point is shadowed
bool is_shadowed(world w, tuple pt);

// compute lighting of a point using Phong reflection model
color lighting(material m,
              point_light l,
              tuple position,
              tuple eye_v,
              tuple normal_v,
              bool in_shadow);

// compute shading intensity for hit points
color shade_hit(world w, computations c);

// compute color at a point where a ray hits an object
color color_at(world w, ray r);

} // end namespace RT
#endif
