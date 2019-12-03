#include "math/perlin.h"

#include <iostream>

using namespace RT;

int main()
{
    perlin& p = perlin::getInstance();
    num_t x, y, z;
    std::cout << "Enter x, y, z: ";
    std::cin >> x;
    std::cin >> y;
    std::cin >> z;
    std::cout << "Noise value: " << p.noise(x, y, z) << '\n';
    return 0;
}

