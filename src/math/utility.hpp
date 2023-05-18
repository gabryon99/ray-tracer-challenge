#ifndef RAYTRACERCHALLENGE_UTILITY_HPP
#define RAYTRACERCHALLENGE_UTILITY_HPP

#include <cmath>
#include <cstdio>

constexpr float EPSILON = 1e-5;

bool compareFloat(float x, float y) {
#ifdef _DEBUG
    std::fprintf(stderr, "x: %4.20f, y: %4.20f, abs(x - y) = %.20f (%d)\n", x, y, std::abs(x - y), std::abs(x - y) <= EPSILON);
#endif
    return std::abs(x - y) <= EPSILON;
}

#endif //RAYTRACERCHALLENGE_UTILITY_HPP
