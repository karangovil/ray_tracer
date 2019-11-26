#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <math.h>

#include "math/tuple.h"
#include "math/matrix4x4.h"

namespace RT
{
    
// Generate Translation matrix
template<typename T>
auto translation(T x, T y, T z)
{
    matrix4x4<T> res;
    res(0,3) = x;
    res(1,3) = y;
    res(2,3) = z;

    return res;
}

// Generate scaling matrix
template<typename T>
auto scaling(T x, T y, T z)
{
    matrix4x4<T> res;
    res(0,0) = x;
    res(1,1) = y;
    res(2,2) = z;

    return res;
}


// Generate rotation matrix
auto rotation_x(double angle)
{
    matrix4x4<double> res;
    res(1,1) = cos(angle);
    res(1,2) = -sin(angle);
    res(2,1) = sin(angle);
    res(2,2) = cos(angle);

    return res;
}

auto rotation_y(double angle)
{
    matrix4x4<double> res;
    res(0,0) = cos(angle);
    res(0,2) = sin(angle);
    res(2,0) = -sin(angle);
    res(2,2) = cos(angle);

    return res;
}

auto rotation_z(double angle)
{
    matrix4x4<double> res;
    res(0,0) = cos(angle);
    res(0,1) = -sin(angle);
    res(1,0) = sin(angle);
    res(1,1) = cos(angle);

    return res;
}

// Generate shearing matrix
template<typename T>
auto shearing(T x_y, T x_z, T y_x, T y_z, T z_x, T z_y)
{
    matrix4x4<T> res;
    res(0,1) = x_y;
    res(0,2) = x_z;
    res(1,0) = y_x;
    res(1,2) = y_z;
    res(2,0) = z_x;
    res(2,1) = z_y;

    return res;
}

template<typename T>
auto view_transform(tuple<T> const& from,
                    tuple<T> const& to,
                    tuple<T> const& up)
{
    auto forward = normalize(to - from);
    auto up_n = normalize(up);
    auto left = cross(forward, up_n);
    auto true_up = cross(left, forward);

    matrix4x4<double> orientation;
    orientation(0,0) = left.x;
    orientation(0,1) = left.y;
    orientation(0,2) = left.z;

    orientation(1,0) = true_up.x;
    orientation(1,1) = true_up.y;
    orientation(1,2) = true_up.z;

    orientation(2,0) = -forward.x;
    orientation(2,1) = -forward.y;
    orientation(2,2) = -forward.z;

    return orientation * translation(-from.x, -from.y, -from.z);
}

} // end namespace RT
#endif
