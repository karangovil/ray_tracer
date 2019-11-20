#ifndef COLORS_H
#define COLORS_H

#include <iostream>

namespace RT
{

// define colors to hold RGB values
template<typename T>
struct color
{
    T red, green, blue;
};

// overload print operator for colors
template<typename T>
std::ostream& operator<<(std::ostream& os, color<T> const& c)
{
    os << "(R: " << c.red << ", G: " << c.green << ", B: " << c.blue << ")\n";
    return os;
}

// overload comparison operator to check equality of colors
template<typename T1, typename T2>
auto operator==(color<T1> const& lhs, color<T2> const& rhs)
{
    return (Approx(lhs.red) == rhs.red) &&
           (Approx(lhs.green) == rhs.green) &&
           (Approx(lhs.blue) == rhs.blue);
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

} // end namespace RT

#endif
