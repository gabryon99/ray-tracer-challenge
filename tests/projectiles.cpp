#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "tuple.hpp"
#include "canvas.hpp"

#include <iostream>

struct Projectile {
    Point  position {Tuple4::point(0, 0, 0)};
    Vector  velocity {Tuple4::vector(0, 0, 0)};
    Projectile(const Tuple4 &position, const Tuple4 &velocity) : position(position), velocity(velocity) {}
};

struct Environment {
    Vector gravity  {Tuple4::vector(0, 0, 0)};
    Vector wind     {Tuple4::vector(0, 0, 0)};
    Environment(const Tuple4 &gravity, const Tuple4 &wind) : gravity(gravity), wind(wind) {}
};

Projectile tick(const Environment& env, const Projectile& proj) {
    auto position = proj.position + proj.velocity;
    auto velocity = proj.velocity + env.gravity + env.wind;
    return {position, velocity};
}

TEST_CASE("Projectile and Environment") {

    Canvas canvas(900, 400);

    // Projectile starts one unit above the origin.
    // Velocity is normalized to 1 unit/tick.
    Projectile p(Tuple4::point(0, 1, 0), Tuple4::vector(1, 1, 0).normalize().value() * 2.f);

    // Gravity -0.1 unit/tick and wind is -0.01 unit/tick
    Environment e(Tuple4::vector(0, -0.1f, 0), Tuple4::vector(-0.01, 0, 0));

    int ticks = 0;

    while (p.position.y >= 0.f) {
        p = tick(e, p);
        ticks += 1;
        canvas.writePixelAt(p.position.x, p.position.y, Pixel(Colors::RED));
        std::cerr << "[info] projectile's position: " << p.position << ", ticks:" << ticks << "\n";
    }

    std::cerr << "[info] projectile landed after '" << ticks << "' ticks\n";
    std::cout << canvas.ppm();

}