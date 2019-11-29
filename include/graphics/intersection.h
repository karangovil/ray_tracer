#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <memory>
#include <vector>
#include <optional>

#include "common.h"

namespace RT
{

struct object;
struct world;
struct ray;

struct intersection
{
public:
    intersection(std::shared_ptr<const object> const& obj, double t);
    intersection& operator=(intersection const& i);
    intersection(intersection const& i);
    
    std::shared_ptr<const object> obj() const { return m_obj; }
    double t() const { return m_t; }
private:
    std::shared_ptr<const object> m_obj;
    double m_t;
};

bool operator==(intersection const& i1, intersection const& i2);

opt_int_v_t intersect_world(world const& w, ray const& r);

std::optional<intersection> hit(std::vector<intersection> const& is);

} // end namespace RT
#endif
