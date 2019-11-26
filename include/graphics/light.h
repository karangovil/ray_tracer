#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "graphics/colors.h"
#include "math/tuple.h"

namespace RT
{

struct point_light
{
public:
    point_light(tuple<double> pos, color<float> intensity)
        : m_position {pos}, m_intensity {intensity} {}

    tuple<double> position() const { return m_position; }
    color<float> intensity() const { return m_intensity; }
private:
    tuple<double> m_position;
    color<float> m_intensity;
};

auto operator==(point_light const& l1, point_light const& l2) -> bool
{
    return (l1.position() == l2.position()) &&
           (l1.intensity() == l2.intensity());
}

} //end namespace RT
#endif
