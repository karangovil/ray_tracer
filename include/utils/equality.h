#ifndef EQUALITY_H
#define EQUALITY_H

#include <cmath>

#include "math/constants.h"

namespace RT
{

inline bool AlmostEquals(float const a, float const b, float TOLERANCE = TOLERANCE_F)
{
    return fabs(a-b) < TOLERANCE;
}

inline bool AlmostEquals(double const a, double const b, double TOLERANCE = TOLERANCE_D)
{
    return fabs(a-b) < TOLERANCE;
}

inline bool AlmostEquals(int const a, int const b, int TOLERANCE = 0)
{
    return abs(a-b) == TOLERANCE;
}

inline bool AlmostEquals(double const a, int const b, double TOLERANCE = TOLERANCE_D)
{
    return fabs(a-b) < TOLERANCE;
}

inline bool AlmostEquals(int const a, double const b, double TOLERANCE = TOLERANCE_D)
{
    return fabs(a-b) < TOLERANCE;
}

inline bool AlmostEquals(int const a, float const b, float TOLERANCE = TOLERANCE_F)
{
    return fabs(a-b) < TOLERANCE;
}

inline bool AlmostEquals(float const a, int const b, float TOLERANCE = TOLERANCE_F)
{
    return fabs(a-b) < TOLERANCE;
}

inline bool AlmostEquals(double const a, float const b, double TOLERANCE = TOLERANCE_D)
{
    return fabs(a-b) < TOLERANCE;
}

inline bool AlmostEquals(float const a, double const b, double TOLERANCE = TOLERANCE_D)
{
    return fabs(a-b) < TOLERANCE;
}

} // end namespace RT
#endif
