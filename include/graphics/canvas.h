#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>

#include "graphics/colors.h"

namespace RT
{

// struct to hold a canvas
struct canvas
{
public:
    canvas(size_t width, size_t height)
        : width {width},
          height {height},
          pixels(width * height, color {0.0, 0.0, 0.0})
    {}

    size_t width, height;
    std::vector<color> pixels;
};

// write a pixel on a canvas
void write_pixel(canvas& c, size_t i, size_t j, color const& col);

// write a pixel on a canvas
color pixel_at(canvas& c, size_t i, size_t j);

// generate a ppm file from a canvas
void canvas_to_ppm(canvas const& c, std::string fname);

} // end namespace RT
#endif
