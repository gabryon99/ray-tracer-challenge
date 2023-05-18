#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "tuple.hpp"
#include "canvas.hpp"

#include <fstream>
#include <thread>
#include <chrono>
#include <iostream>

struct Projectile {
    Point   position {point(0, 0, 0)};
    Vector  velocity {vector(0, 0, 0)};
    Projectile(const Tuple4 &position, const Tuple4 &velocity) : position(position), velocity(velocity) {}
};

struct Environment {
    Vector gravity  {vector(0, 0, 0)};
    Vector wind     {vector(0, 0, 0)};
    Environment(const Tuple4 &gravity, const Tuple4 &wind) : gravity(gravity), wind(wind) {}
};

Projectile tick(const Environment& env, const Projectile& proj) {
    auto position = proj.position + proj.velocity;
    auto velocity = proj.velocity + env.gravity + env.wind;
    return {position, velocity};
}

TEST_CASE("Draw a Square") {

    Canvas canvas(500, 500);

    Point startingPoint = point(100, 100, 0);
    for (size_t i = 0; i < 300; i++) {
        canvas.writePixelAt(startingPoint.x + i, startingPoint.y, Pixel(Colors::RED));
        canvas.writePixelAt(startingPoint.x, startingPoint.y + i, Pixel(Colors::RED));
        canvas.writePixelAt(startingPoint.x + 300, canvas.height - startingPoint.y - i, Pixel(Colors::RED));
        canvas.writePixelAt(startingPoint.x + i, startingPoint.y + 300, Pixel(Colors::RED));

    }

    std::ofstream outputFile;
    outputFile.open("./square.ppm", std::ofstream::out | std::ofstream::trunc);
    outputFile << canvas.ppm();
    outputFile.close();

}

TEST_CASE("Projectile and Environment") {

    Canvas canvas(400, 400);

    // Projectile starts one unit above the origin.
    // Velocity is normalized to 1 unit/tick.
    Projectile p(point(0, 1, 0),vector(1, 1, 0).normalize().value() * 4);

    // Gravity -0.1 unit/tick and wind is -0.01 unit/tick
    Environment env(vector(0, -0.1f, 0),vector(-0.01, 0, 0));

    int ticks {0};

    while (p.position.y >= 0.f) {
        std::cerr << "[info] projectile's position: " << p.position << ", ticks:" << ticks << "\n";
        p = tick(env, p);
        ticks += 1;

        auto x = std::clamp(static_cast<int>(p.position.x), 0, static_cast<int>(canvas.width));
        auto y = std::clamp(static_cast<int>(canvas.height - p.position.y), 0, static_cast<int>(canvas.height));

        canvas.writePixelAt(x, y, Pixel(Colors::GREEN));
    }

    std::cerr << "[info] projectile landed after '" << ticks << "' ticks\n";

    std::ofstream outputFile;
    outputFile.open("./projectile.ppm", std::ofstream::out | std::ofstream::trunc);
    outputFile << canvas.ppm();
    outputFile.close();

}