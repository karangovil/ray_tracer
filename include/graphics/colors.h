#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include "utils/equality.h"

namespace RT
{

// define colors to hold RGB values
template<typename T>
struct color
{
    T red, green, blue;
};

// deduction guides for color<T>
color(int, int, int) -> color<int>;
color(float, float, float) -> color<float>;
color(double, double, double) -> color<double>;

// overload print operator for colors
template<typename T>
std::ostream& operator<<(std::ostream& os, color<T> const& c)
{
    os << "(R: " << c.red << ", G: " << c.green << ", B: " << c.blue << ")\n";
    return os;
}

// overload comparison operator to check equality of colors
inline auto operator==(color<float> const& lhs, color<float> const& rhs)
{
    return AlmostEquals(lhs.red, rhs.red, 0.0001f) &&
           AlmostEquals(lhs.green, rhs.green, 0.0001f) &&
           AlmostEquals(lhs.blue, rhs.blue, 0.0001f);
}

inline auto operator==(color<double> const& lhs, color<double> const& rhs)
{
    return AlmostEquals(lhs.red, rhs.red, 1e-4) &&
           AlmostEquals(lhs.green, rhs.green, 1e-4) &&
           AlmostEquals(lhs.blue, rhs.blue, 1e-4);
}

inline auto operator==(color<float> const& lhs, color<double> const& rhs)
{
    return AlmostEquals(lhs.red, rhs.red, 1e-4) &&
           AlmostEquals(lhs.green, rhs.green, 1e-4) &&
           AlmostEquals(lhs.blue, rhs.blue, 1e-4);
}

inline auto operator==(color<double> const& lhs, color<float> const& rhs)
{
    return AlmostEquals(lhs.red, rhs.red, 1e-4) &&
           AlmostEquals(lhs.green, rhs.green, 1e-4) &&
           AlmostEquals(lhs.blue, rhs.blue, 1e-4);
}

inline auto operator==(color<int> const& lhs, color<int> const& rhs)
{
    return AlmostEquals(lhs.red, rhs.red) &&
           AlmostEquals(lhs.green, rhs.green) &&
           AlmostEquals(lhs.blue, rhs.blue);
}

// overload addition for colors
template<typename T1, typename T2>
auto operator+(color<T1> c1, color<T2> c2)
{
    return color<decltype(c1.red + c2.red)> { c1.red + c2.red,
                                              c1.green + c2.green,
                                              c1.blue + c2.blue };
}

// overload subtraction for colors
template<typename T1, typename T2>
auto operator-(color<T1> c1, color<T2> c2)
{
    return color<decltype(c1.red - c2.red)> { c1.red - c2.red,
                                              c1.green - c2.green,
                                              c1.blue - c2.blue };
}

// overload multiplication for colors
template<typename T1, typename T2>
auto operator*(color<T1> c1, color<T2> c2)
{
    return color<decltype(c1.red * c2.red)> { c1.red * c2.red,
                                              c1.green * c2.green,
                                              c1.blue * c2.blue };
}

// overload scalar multiplication
template<typename T1, typename T2>
auto operator*(color<T1> c, T2 s)
{
    return color<decltype(c.red * s)> { c.red * s,
                                        c.green * s,
                                        c.blue * s };
}

} // end namespace RT

#endif
