#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "colors.h"
#include "tuple.h"

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

} //end namespace RT
#endif
