#include <vector>

#include "math/transformations.h"
#include "shapes/sphere.h"
#include "shapes/material.h"
#include "shapes/object.h"
#include "graphics/canvas.h"
#include "graphics/world.h"
#include "graphics/camera.h"
#include "graphics/colors.h"

using namespace RT;

int main()
{
    camera c {600, 300, 0.524};
    c.set_transform(view_transform(point(40, 0, -70),
                                   point(0, 0, -5),
                                   vector(0, 1, 0)));

    world w;
    w.set_light(point_light {point(0, 0, -100), color {1.0, 1.0, 1.0}});

    material sphere_material {0.2, 0.8, 0.3, 200, {1.0, 1.0, 1.0}};

    material wrist_material {sphere_material};
    wrist_material.set_color({0.1, 1, 1});

    material palm_material {sphere_material};
    palm_material.set_color({0.1, 0.1, 1});

    material thumb_material {sphere_material};
    thumb_material.set_color({0.1, 0.1, 1});

    material index_material {sphere_material};
    index_material.set_color({1, 1, 0.1});

    material middle_material {sphere_material};
    middle_material.set_color({0.1, 1, 0.5});

    material ring_material {sphere_material};
    ring_material.set_color({0.1, 1, 0.1});

    material pinky_material {sphere_material};
    pinky_material.set_color({0.1, 0.5, 1});

    sphere s;
    s.set_transform(scaling(200, 200, 0.01) * translation(0, 0, 20));
    material m_s {0, 0.5, 0, 200, {1, 1, 1}};
    s.set_material(m_s);

    sphere wrist_sphere;
    wrist_sphere.set_material(wrist_material);
    wrist_sphere.set_transform(rotation_z(M_PI / 4) *
                               translation(-4, 0, -21) *
                               scaling(3, 3, 3));
    
    sphere palm_sphere;
    palm_sphere.set_transform(translation(0, 0, -15) *
                              scaling(4, 3, 3));
    palm_sphere.set_material(palm_material);
    
    sphere thumb_sphere;
    thumb_sphere.set_transform(translation(-2, 2, -16) *
                               scaling(1, 3, 1));
    thumb_sphere.set_material(thumb_material);
    
    sphere index_sphere;
    index_sphere.set_transform(translation(3, 2, -22) *
                               scaling(3, 0.75, 0.75));
    index_sphere.set_material(thumb_material);
    
    sphere middle_sphere;
    middle_sphere.set_transform(translation(4, 1, -19) *
                                scaling(3, 0.75, 0.75));
    middle_sphere.set_material(middle_material);
    
    sphere ring_sphere;
    ring_sphere.set_transform(translation(4, 0, -18) *
                              scaling(3, 0.75, 0.75));
    ring_sphere.set_material(ring_material);
    
    sphere pinky_sphere;
    pinky_sphere.set_transform(translation(3, -1.5, -20) *
                               rotation_z(-M_PI / 10) * 
                               translation(1, 0, 0) * 
                               scaling(2.5, 0.6, 0.6));
    pinky_sphere.set_material(pinky_material); 
    
    std::vector<std::shared_ptr<object>> objs;
    objs.emplace_back(std::make_shared<sphere>(s));
    objs.emplace_back(std::make_shared<sphere>(wrist_sphere));
    objs.emplace_back(std::make_shared<sphere>(palm_sphere));
    objs.emplace_back(std::make_shared<sphere>(thumb_sphere));
    objs.emplace_back(std::make_shared<sphere>(index_sphere));
    objs.emplace_back(std::make_shared<sphere>(middle_sphere));
    objs.emplace_back(std::make_shared<sphere>(ring_sphere));
    objs.emplace_back(std::make_shared<sphere>(pinky_sphere));
   
    w.set_objs(objs);

    auto canv = render(c, w);
    canvas_to_ppm(canv, "shadowPuppet");

    return 0;
}
