#ifndef COMMON_H
#define COMMON_H

#define _USE_MATH_DEFINES

#include <optional>
#include <vector>

namespace RT
{

struct intersection;
using num_t = double;
using opt_int_v_t = std::optional<std::vector<intersection>>;

}

#endif
