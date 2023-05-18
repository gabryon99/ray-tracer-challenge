#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <sstream>

#include "canvas.hpp"


TEST_CASE("Canvas") {

    SUBCASE("Creating a canvas") {
        Canvas canvas(10, 20);
        CHECK_EQ(canvas.width, 10);
        CHECK_EQ(canvas.height, 20);
    }

    SUBCASE("Writing pixel to a canvas") {
        Canvas canvas(10, 20);
        canvas.writePixelAt(2, 3, Pixel(Colors::RED));
        CHECK_EQ(canvas.pixelAt(2, 3).color, Colors::RED);
    }

    SUBCASE("Constructing the PPM Header") {

        Canvas canvas(5, 3);
        io::PPM canvasPPM = canvas.ppm();

        std::stringstream stream{};
        stream << canvasPPM.header;

        std::string canvasPPMStr = stream.str();

        CHECK_EQ(canvasPPMStr, "P3\n5 3\n255");
    }
}

