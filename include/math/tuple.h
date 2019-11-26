#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>
#include <iostream>

#include "utils/equality.h"

namespace RT
{

template<typename T>
struct tuple
{
    T x, y, z, w;
};

// print a tuple
template<typename T>
std::ostream& operator<<(std::ostream& os, tuple<T> const& t)
{
    os << "(" << t.x << ", " << t.y << ", " << t.z << ")\n";
    return os;
}

// create a point from (x,y,z) coordinates
template<typename T>
auto point(T const x, T const y, T const z) -> tuple<T>
{ return tuple<T> { x, y, z, static_cast<T>(1.0) }; } 

// create a vector from (x,y,x) coordinates
template<typename T>
auto vector(T const x, T const y, T const z) -> tuple<T>
{ return tuple<T> { x, y, z, static_cast<T>(0.0) }; } 

// overload comparison operator to check equality of tuples
template<typename T1, typename T2>
auto operator==(tuple<T1> const& lhs, tuple<T2> const& rhs)
{
    return AlmostEquals(lhs.x, rhs.x) &&
           AlmostEquals(lhs.y, rhs.y) &&
           AlmostEquals(lhs.z, rhs.z) &&
           AlmostEquals(lhs.w, rhs.w);
}

// overload addition to add tuples element-wise
template<typename T1, typename T2>
auto operator+(tuple<T1> const& t1, tuple<T2> const& t2)
{ 
    return tuple<decltype(t1.x + t2.x)> { t1.x + t2.x,
                                          t1.y + t2.y,
                                          t1.z + t2.z,
                                          t1.w + t2.w };
}

// overload subtraction to add tuples element-wise
template<typename T1, typename T2>
auto operator-(tuple<T1> const& t1, tuple<T2> const& t2)
{ 
    return tuple<decltype(t1.x - t2.x)> { t1.x - t2.x,
                                          t1.y - t2.y,
                                          t1.z - t2.z,
                                          t1.w - t2.w };
}

// negation of tuple
template<typename T>
auto operator-(tuple<T> const& t) -> tuple<T>
{ return tuple<T> { -t.x, -t.y, -t.z, -t.w }; }

// scalar multiplication
template<typename T1, typename T2>
auto operator*(T1 s, tuple<T2> t)
{ return tuple<decltype(s * t.x)> { s * t.x, s * t.y, s * t.z, s * t.w }; }

// scalar multiplication
template<typename T1, typename T2>
auto operator*(tuple<T1> t, T2 s)
{ return s * t; }

// scalar multiplication
template<typename T1, typename T2>
auto operator/(tuple<T1> t, T2 s)
{ return tuple<decltype(t.x / s)> { t.x / s, t.y / s, t.z / s, t.w / s }; }

// dot product
template<typename T1, typename T2>
auto dot(tuple<T1> t1, tuple<T2> t2)
{ 
    return (t1.x * t2.x +
            t1.y * t2.y +
            t1.z * t2.z +
            t1.w * t2.w);
}

// cross product of two vectors
template<typename T1, typename T2>
auto cross(tuple<T1> t1, tuple<T2> t2)
{
    return vector(t1.y * t2.z - t1.z * t2.y,
                  t1.z * t2.x - t1.x * t2.z,
                  t1.x * t2.y - t1.y * t2.x);
}

// magnitude of a tuple
template<typename T>
auto magnitude(tuple<T> t)
{ return sqrt(dot(t, t)); }

// normalize a tuple
template<typename T>
auto normalize(tuple<T> t)
{ return t / magnitude(t); }

// check if a tuple is a point
template<typename T>
auto is_point(tuple<T> const& tup) -> bool
{ return tup.w == static_cast<T>(1.0); }

// check if a tuple is a vector
template<typename T>
auto is_vector(tuple<T> const& tup) -> bool
{ return tup.w == static_cast<T>(0.0); }

} // end namespace RT
#endif
