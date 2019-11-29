#include <vector>

#include "math/transformations.h"
#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "shapes/material.h"
#include "shapes/object.h"
#include "graphics/canvas.h"
#include "graphics/world.h"
#include "graphics/camera.h"
#include "graphics/colors.h"

using namespace RT;

int main()
{
    plane floor;
    material m_floor;
    m_floor.set_color(color {1.0, 0.9, 0.9});
    m_floor.set_specular(0.0);
    floor.set_material(m_floor);

    // sphere left_wall;
    // left_wall.set_transform(translation(0.0, 0.0, 5.0) *
    //                         rotation_y(-M_PI / 4.0) * rotation_x(M_PI / 2.0) *
    //                         scaling(10.0, 0.01, 10.0));
    // left_wall.set_material(m_floor);
    //
    // sphere right_wall;
    // right_wall.set_transform(translation(0.0, 0.0, 5.0) *
    //                         rotation_y(M_PI / 4.0) * rotation_x(M_PI / 2.0) *
    //                         scaling(10.0, 0.01, 10.0));
    // right_wall.set_material(m_floor);

    sphere middle;
    middle.set_transform(translation(-0.5, 1.0, 0.5));
    material m_middle;
    m_middle.set_color(color {0.5, 1.0, 0.1});
    m_middle.set_diffuse(0.7);
    m_middle.set_specular(0.3);
    middle.set_material(m_middle);

    sphere right;
    right.set_transform(translation(1.0, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    material m_right;
    m_right.set_color(color {1.0, 0.8, 0.1});
    m_right.set_diffuse(0.7);
    m_right.set_specular(0.3);
    right.set_material(m_right);

    sphere left;
    left.set_transform(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    material m_left;
    m_left.set_color(color {1.0, 0.8, 0.1});
    m_left.set_diffuse(0.7);
    m_left.set_specular(0.3);
    left.set_material(m_left);
    
    world w;
    w.set_light(point_light {point(-10.0, 10.0, -10.0), color {1.0, 1.0, 1.0}});

    std::vector<std::shared_ptr<object>> objs;
    objs.emplace_back(std::make_shared<plane>(floor));
    // objs.emplace_back(std::make_shared<sphere>(left_wall));
    // objs.emplace_back(std::make_shared<sphere>(right_wall));
    objs.emplace_back(std::make_shared<sphere>(middle));
    objs.emplace_back(std::make_shared<sphere>(right));
    objs.emplace_back(std::make_shared<sphere>(left));
   
    w.set_objs(objs);

    camera c {500, 250, M_PI / 3.0};
    c.set_transform(view_transform(point(0.0, 1.5, -5.0),
                                   point(0.0, 1.0, 0.0),
                                   vector(0.0, 1.0, 0.0)));

    auto canv = render(c, w);
    canvas_to_ppm(canv, "multipleSpheresPlane");

    return 0;
}
