#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <math.h>
#include "tuple.h"
#include "matrix4x4.h"

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

} // end namespace RT
#endif
