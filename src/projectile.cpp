#include "tuple.h"
#include "canvas.h"
#include <cmath>

using namespace RT;

struct projectile
{
    projectile(tuple<double> pos, tuple<double> vel)
        : position(pos), velocity(vel) {}

    tuple<double> position;
    tuple<double> velocity;
};

struct environment
{
    environment(tuple<double> grav, tuple<double> wind)
        : gravity(grav), wind(wind) {}

    tuple<double> gravity;
    tuple<double> wind;
};

auto tick(environment env, projectile proj) -> projectile
{
    auto position = proj.position + proj.velocity;
    auto velocity = proj.velocity + env.gravity + env.wind;
    return { position, velocity };
}

template<typename T>
auto inRange(T x, T lo, T hi) -> bool
{ return ((x - hi) * (x - lo) <= static_cast<T>(0.0)); }

int main()
{
    auto start = point(0.0, 1.0, 0.0);
    auto velocity = normalize(vector(1.0, 1.8, 0.0)) * 11.25;
    projectile p { start, velocity };

    auto gravity = vector(0.0, -0.1, 0.0);
    auto wind = vector(-0.01, 0.0, 0.0);
    environment e { gravity, wind };

    size_t canvas_x = 900;
    size_t canvas_y = 550;

    canvas c { canvas_x, canvas_y };

    color<float> red {1.0, 0.0, 0.0 };

    while (true)
    {
        p = tick(e, p);
        if (p.position.y >= 0.0)
        {
            size_t pos_x = std::round(p.position.x);
            size_t pos_y = (canvas_y - std::round(p.position.y));
            // size_t pos_y = std::round(p.position.y);
            
            // std::cout << "X position: " << pos_x << ", ";
            // std::cout << "Y position: " << pos_y << '\n';
            if (inRange<int>(pos_x, 0, canvas_x) && 
                inRange<int>(pos_y, 0, canvas_y))
                write_pixel(c, pos_y, pos_x, red);
        }
        else    
            break;
    }

    canvas_to_ppm(c, "projectile");

    return 0;
}
