#ifndef TEST_PATTERN_H
#define TEST_PATTERN_H

#include "shapes/patterns.h"
#include "math/matrix4x4.h"
#include "graphics/colors.h"

using namespace RT;

struct test_pattern : public pattern
{
public:
    test_pattern()
        : pattern {color {1, 1, 1}, color {0, 0, 0}} {}

    color pattern_at(tuple const& pt) const
    { return color {pt.x, pt.y, pt.z}; }
};

#endif
