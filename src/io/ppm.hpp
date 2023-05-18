#ifndef RAYTRACERCHALLENGE_PPM_HPP
#define RAYTRACERCHALLENGE_PPM_HPP

#include <string>
#include <ostream>
#include <algorithm>

#include "../pixel.hpp"

namespace io {

    enum class PPMIdentifier {
        BITMAP,
        GRAYMAP,
        COLORMAP
    };

    struct PPMHeader {
        PPMIdentifier magic;
        uint32_t width{0};
        uint32_t height{0};
        uint32_t maximumColorValue{0xff};

        PPMHeader(const PPMIdentifier &magic, uint32_t width, uint32_t height, uint32_t maximumColorValue) : magic(magic),
                                                                                                           width(width),
                                                                                                           height(height),
                                                                                                           maximumColorValue(
                                                                                                                   maximumColorValue) {}
        std::string magicIdentifier() const {
            switch (magic) {
                case PPMIdentifier::BITMAP: return "P1";
                case PPMIdentifier::GRAYMAP: return "P2";
                case PPMIdentifier::COLORMAP: return "P3";
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const PPMHeader &header) {
            os << header.magicIdentifier() << "\n";
            os << header.width << " " << header.height << "\n";
            os << header.maximumColorValue;
            return os;
        }
    };

    struct PPM {
        PPMHeader header;
        std::vector<Pixel> data;

        explicit PPM(const PPMHeader header, const std::vector<Pixel> &_data) : header(header) {
            std::copy(_data.begin(), _data.end(), std::back_inserter(data));
        }

        friend std::ostream &operator<<(std::ostream &os, const PPM &ppm) {
            os << ppm.header << "\n";
            for (std::size_t i = 0; i < ppm.header.width; i += 1) {
                for (std::size_t j = 0; j < ppm.header.height; j += 1) {
                    auto pixel = &ppm.data[j + i * ppm.header.width];

                    auto red = static_cast<int>(pixel->color.x * ppm.header.maximumColorValue);
                    auto green = static_cast<int>(pixel->color.y * ppm.header.maximumColorValue);
                    auto blue = static_cast<int>(pixel->color.z * ppm.header.maximumColorValue);

                    os << std::clamp(red, 0, static_cast<int>(ppm.header.maximumColorValue)) << " "
                       << std::clamp(green, 0, static_cast<int>(ppm.header.maximumColorValue)) << " "
                       << std::clamp(blue, 0, static_cast<int>(ppm.header.maximumColorValue)) << "\t";
                }
            }
            os << "\n";
            return os;
        }
    };
}

#endif //RAYTRACERCHALLENGE_PPM_HPP
