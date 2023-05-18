#ifndef RAYTRACERCHALLENGE_PIXEL_HPP
#define RAYTRACERCHALLENGE_PIXEL_HPP

#include "color.hpp"

struct Pixel {

    Color color {Colors::BLACK};

    constexpr explicit Pixel(const Color &color = Colors::BLACK) : color(color) {}

    bool operator==(const Pixel &rhs) const { return color == rhs.color; }
    bool operator!=(const Pixel &rhs) const { return !(rhs == *this); }
};

#endif //RAYTRACERCHALLENGE_PIXEL_HPP
