#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>
#include <iostream>

#include "common.h"
#include "utils/equality.h"

namespace RT
{

struct tuple
{
    num_t x, y, z, w;
};

// print a tuple
inline
std::ostream& operator<<(std::ostream& os, tuple const& t)
{
    os << "(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")\n";
    return os;
}

// create a point from (x,y,z) coordinates
inline
tuple point(num_t const x, num_t const y, num_t const z)
{ return tuple { x, y, z, static_cast<num_t>(1.0) }; } 

// create a vector from (x,y,x) coordinates
inline
tuple vector(num_t const x, num_t const y, num_t const z)
{ return tuple { x, y, z, static_cast<num_t>(0.0) }; } 

// check if a tuple is a point
inline
bool is_point(tuple const& tup)
{ return tup.w == static_cast<num_t>(1.0); }

// check if a tuple is a vector
inline
bool is_vector(tuple const& tup)
{ return tup.w == static_cast<num_t>(0.0); }

// overload comparison operator to check equality of tuples
inline
auto operator==(tuple const& lhs, tuple const& rhs)
{
    return AlmostEquals(lhs.x, rhs.x) &&
           AlmostEquals(lhs.y, rhs.y) &&
           AlmostEquals(lhs.z, rhs.z) &&
           AlmostEquals(lhs.w, rhs.w);
}

// overload addition to add tuples element-wise
inline
auto operator+(tuple const& t1, tuple const& t2)
{ 
    return tuple { t1.x + t2.x,
                   t1.y + t2.y,
                   t1.z + t2.z,
                   t1.w + t2.w };
}

// overload subtraction to add tuples element-wise
inline
auto operator-(tuple const& t1, tuple const& t2)
{ 
    return tuple { t1.x - t2.x,
                   t1.y - t2.y,
                   t1.z - t2.z,
                   t1.w - t2.w };
}

// negation of tuple
inline
auto operator-(tuple const& t)
{ return tuple { -t.x, -t.y, -t.z, -t.w }; }

// scalar multiplication
inline
auto operator*(num_t s, tuple t)
{ return tuple { s * t.x, s * t.y, s * t.z, s * t.w }; }

// scalar multiplication
inline
auto operator*(tuple t, num_t s)
{ return s * t; }

// scalar multiplication
inline
auto operator/(tuple t, num_t s)
{ return tuple { t.x / s, t.y / s, t.z / s, t.w / s }; }

// dot product
inline
auto dot(tuple t1, tuple t2)
{ 
    return (t1.x * t2.x +
            t1.y * t2.y +
            t1.z * t2.z +
            t1.w * t2.w);
}

// cross product of two vectors
inline
auto cross(tuple t1, tuple t2)
{
    return vector(t1.y * t2.z - t1.z * t2.y,
                  t1.z * t2.x - t1.x * t2.z,
                  t1.x * t2.y - t1.y * t2.x);
}

// magnitude of a tuple
inline
auto magnitude(tuple t)
{ return std::sqrt(dot(t, t)); }

// normalize a tuple
inline
auto normalize(tuple t)
{ return t / magnitude(t); }

} // end namespace RT
#endif
