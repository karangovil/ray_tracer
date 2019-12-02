#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include <memory>

#include "math/tuple.h"
#include "math/constants.h"

namespace RT
{

struct object;
struct intersection;
struct ray;

struct computations
{
public:
    computations(intersection i, ray r);

    auto t() const { return m_t; }
    auto obj() const { return m_obj; }
    auto point() const { return m_point; }
    auto over_point() const { return m_over_point; }
    auto eye_v() const { return m_eye_v; }
    auto normal_v() const { return m_normal_v; }
    auto inside() const { return m_inside; }
private:
    double m_t;
    std::shared_ptr<object> m_obj;
    tuple m_point, m_over_point, m_eye_v, m_normal_v;
    bool m_inside;
};

} // end namespace RT

#endif
