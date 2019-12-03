#include <vector>

#include "math/transformations.h"
#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "shapes/material.h"
#include "patterns.h"
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
    color white {1, 1, 1};
    color black {0, 0, 0};
    gradient_pattern s {color {52.0 / 255.0, 235.0 / 255.0, 149.0 / 255.0},
                       color {52.0 / 255.0, 128.0 / 255.0, 235.0 / 255.0}};
    s.set_transform(scaling(0.1, 1, 2));
    std::shared_ptr<pattern> p_floor = std::make_shared<gradient_pattern>(s); 
    m_floor.set_pattern(p_floor);
    m_floor.set_color(color {1.0, 0.9, 0.9});
    m_floor.set_specular(0.0);
    floor.set_material(m_floor);

    sphere middle;
    middle.set_transform(translation(-0.5, 1.0, 0.5));
    material m_middle;
    gradient_pattern s_middle {white, black};//, 20, 10};
    s_middle.set_transform(rotation_z(M_PI/2) * scaling(0.9, 1, 1));
    std::shared_ptr<pattern> p_middle_sphere =
        std::make_shared<gradient_pattern>(s_middle);
    m_middle.set_pattern(p_middle_sphere);
    m_middle.set_color(color {0.5, 1.0, 0.1});
    m_middle.set_diffuse(0.7);
    m_middle.set_specular(0.3);
    middle.set_material(m_middle);

    sphere right;
    gradient_pattern s_right {color {1.0, 0.8, 0.1}, 
                              color {0.1, 0.8, 1.0}};//, 20, 10};
    material m_right;
    s_right.set_transform(rotation_z(M_PI/5) * scaling(0.9, 1, 1));
    std::shared_ptr<pattern> p_right_sphere =
        std::make_shared<gradient_pattern>(s_right);
    m_right.set_pattern(p_right_sphere);
    right.set_transform(translation(1.0, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    m_right.set_color(color {1.0, 0.8, 0.1});
    m_right.set_diffuse(0.7);
    m_right.set_specular(0.3);
    right.set_material(m_right);

    sphere left;
    left.set_transform(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    material m_left;
    gradient_pattern s_left {color {0.5, 0.2, 0.1}, 
                             color {0.3, 0.8, 0.5}};//, 20, 10};
    s_left.set_transform(rotation_z(M_PI/10) * scaling(0.9, 1, 1));
    std::shared_ptr<pattern> p_left_sphere =
        std::make_shared<gradient_pattern>(s_left);
    m_left.set_pattern(p_left_sphere);
    m_left.set_color(color {1.0, 0.8, 0.1});
    m_left.set_diffuse(0.7);
    m_left.set_specular(0.3);
    left.set_material(m_left);
    
    world w;
    w.set_light(point_light {point(-10.0, 10.0, -10.0), color {1.0, 1.0, 1.0}});

    std::vector<std::shared_ptr<object>> objs;
    objs.emplace_back(std::make_shared<plane>(floor));
    objs.emplace_back(std::make_shared<sphere>(middle));
    objs.emplace_back(std::make_shared<sphere>(right));
    objs.emplace_back(std::make_shared<sphere>(left));
   
    w.set_objs(objs);

    camera c {500, 250, M_PI / 3.0};
    c.set_transform(view_transform(point(0.0, 1.5, -5.0),
                                   point(0.0, 1.0, 0.0),
                                   vector(0.0, 1.0, 0.0)));

    auto canv = render(c, w, true);
    canvas_to_ppm(canv, "patterns");

    return 0;
}
