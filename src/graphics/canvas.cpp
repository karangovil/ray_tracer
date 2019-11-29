#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "graphics/canvas.h"

namespace RT
{

// write a pixel on a canvas
void write_pixel(canvas& c, size_t i, size_t j, color const& col)
{ c.pixels[i * c.width + j] = col; }

// write a pixel on a canvas
color pixel_at(canvas& c, size_t i, size_t j)
{ return c.pixels[i * c.width + j]; }

void canvas_to_ppm(canvas const& c, std::string fname)
{
    std::ofstream ppm;

    ppm.open(fname + ".ppm");

    // ppm << "\"\"\"\n";
    ppm << "P3\n";
    ppm << c.width << " " << c.height << '\n';
    ppm << "255\n";

    for (auto const& pixel : c.pixels)
    {
        ppm << std::round(std::clamp(pixel.red * 255.0,   0.0, 255.0)) << " " <<
               std::round(std::clamp(pixel.green * 255.0, 0.0, 255.0)) << " " <<
               std::round(std::clamp(pixel.blue * 255.0,  0.0, 255.0)) << " " << '\n';
    }

    ppm << '\n';


    ppm.close();
}

} // end namespace RT
