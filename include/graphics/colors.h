#ifndef COLORS_H
#define COLORS_H

#include <iostream>

#include "common.h"
#include "utils/equality.h"

namespace RT
{

// define colors to hold RGB values
struct color
{
    num_t red, green, blue;
};

// overload print operator for colors
inline
std::ostream& operator<<(std::ostream& os, color const& c)
{
    os << "(R: " << c.red << ", G: " << c.green << ", B: " << c.blue << ")\n";
    return os;
}

// overload comparison operator to check equality of colors
inline auto operator==(color const& lhs, color const& rhs)
{
    return AlmostEquals(lhs.red, rhs.red, static_cast<num_t>(1e-4)) &&
           AlmostEquals(lhs.green, rhs.green, static_cast<num_t>(1e-4)) &&
           AlmostEquals(lhs.blue, rhs.blue, static_cast<num_t>(1e-4));
}

// overload addition for colors
inline
auto operator+(color c1, color c2)
{
    return color { c1.red + c2.red,
                   c1.green + c2.green,
                   c1.blue + c2.blue };
}

// overload subtraction for colors
inline
auto operator-(color c1, color c2)
{
    return color { c1.red - c2.red,
                   c1.green - c2.green,
                   c1.blue - c2.blue };
}

// overload multiplication for colors
inline
auto operator*(color c1, color c2)
{
    return color { c1.red * c2.red,
                   c1.green * c2.green,
                   c1.blue * c2.blue };
}

// overload scalar multiplication
inline
auto operator*(color c, num_t s)
{
    return color { c.red * s,
                   c.green * s,
                   c.blue * s };
}

} // end namespace RT

#endif
