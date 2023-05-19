#ifndef RAYTRACERCHALLENGE_UTILITY_HPP
#define RAYTRACERCHALLENGE_UTILITY_HPP

#include <cmath>
#include <cstdio>

constexpr float EPSILON = 1e-5;
constexpr float PI = M_PI;
constexpr float SQR_TWO = 1.4142135623730951;

bool compareFloat(float x, float y) {
#ifdef _DEBUG
    std::fprintf(stderr, "x: %4.20f, y: %4.20f, abs(x - y) = %.20f (%d)\n", x, y, std::abs(x - y), std::abs(x - y) <= EPSILON);
#endif
    return std::abs(x - y) <= EPSILON;
}

float radians(float deg) { return (deg / 180.0f) * M_PI; }

#endif //RAYTRACERCHALLENGE_UTILITY_HPP
