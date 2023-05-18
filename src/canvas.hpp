#ifndef RAYTRACERCHALLENGE_CANVAS_HPP
#define RAYTRACERCHALLENGE_CANVAS_HPP

#include <vector>
#include <cstdint>

#include "pixel.hpp"

#include "math/tuple.hpp"
#include "io/ppm.hpp"


class Canvas {

    std::vector<Pixel> pixels;

public:

    uint32_t width {0};
    uint32_t height {0};

    Canvas(uint32_t width, uint32_t height) : width{width}, height{height} {
        pixels.resize(width * height);
    }

    [[nodiscard]] Pixel pixelAt(size_t x, size_t y) const {
        return pixels[x + y * width];
    }

    void writePixelAt(size_t x, size_t y, Pixel pixel) {
        pixels[x + y * width] = pixel;
    }

    io::PPM ppm() const {
        return io::PPM(
                io::PPMHeader(io::PPMIdentifier::COLORMAP, width, height, 0xff),
                pixels);
    }

};

#endif //RAYTRACERCHALLENGE_CANVAS_HPP
