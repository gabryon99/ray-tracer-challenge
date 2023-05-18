#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "tuple4.hpp"

TEST_CASE("testing the Tuple4 class") {

    SUBCASE("a tuple with w=1.0 is a point") {
        Tuple4 a(4.3f, -4.2f, 3.1f, 1.0f);
        CHECK_EQ(a.x, 4.3f);
        CHECK_EQ(a.y, -4.2f);
        CHECK_EQ(a.z, 3.1f);
        CHECK_EQ(a.w, 1.0);

        CHECK_EQ(a.isPoint(), true);
        CHECK_EQ(a.isVector(), false);
    }

    SUBCASE("a tuple with w=0.0 is a vector") {
        Tuple4 a(4.3f, -4.2f, 3.1f, 0.0f);
        CHECK_EQ(a.x, 4.3f);
        CHECK_EQ(a.y, -4.2f);
        CHECK_EQ(a.z, 3.1f);
        CHECK_EQ(a.w, 0.0f);

        CHECK_EQ(a.isPoint(), false);
        CHECK_EQ(a.isVector(), true);
    }

    SUBCASE("Tuple4::point create tuple with w=1.0f") {
        Tuple4 p = Tuple4::point(4.f, -4.f, 3.f);
        CHECK_EQ(p, Tuple4(4.f, -4.f, 3.f, 1.f));
    }

    SUBCASE("Tuple4::vector create tuple with w=0.0f") {
        Tuple4 v = Tuple4::vector(4.f, -4.f, 3.f);
        CHECK_EQ(v, Tuple4(4.f, -4.f, 3.f, 0.f));
    }

    SUBCASE("Adding two tuples") {
        Tuple4 a1(3.f, -2.f, 5.f, 1.f);
        Tuple4 a2(-2.f, 3.f, 1.f, 0.f);
        CHECK_EQ(a1 + a2, Tuple4(1.f, 1.f, 6.f, 1.f));
    }

    SUBCASE("Subtracting two points") {
        auto p1 = Tuple4::point(3, 2, 1);
        auto p2 = Tuple4::point(5, 6, 7);
        CHECK_EQ(p1 - p2, Tuple4::vector(-2, -4, -6));
    }

    SUBCASE("Subtracting a vector from a point") {
        auto p = Tuple4::point(3, 2, 1);
        auto v = Tuple4::vector(5, 6, 7);
        CHECK_EQ(p -v, Tuple4::point(-2, -4, -6));
    }

    SUBCASE("Subtracting two vectors") {
        auto v1 = Tuple4::vector(3, 2, 1);
        auto v2 = Tuple4::vector(5, 6, 7);
        CHECK_EQ(v1 - v2, Tuple4::vector(-2, -4, -6));
    }

    SUBCASE("Subtracting a vector from the zero vector") {
        auto zero = Tuple4::vector(0, 0, 0);
        auto v = Tuple4::vector(1, -2, 3);
        CHECK_EQ(zero - v, Tuple4::vector(-1, 2, -3));
    }

    SUBCASE("Negating a tuple") {
        Tuple4 a(1, -2, 3, -4);
        CHECK_EQ(-a, Tuple4(-1, 2, -3, 4));
    }

    SUBCASE("Multiplying a tuple by a scalar") {
        Tuple4 a(1, -2, 3, -4);
        CHECK_EQ(a * 3.5f, Tuple4(3.5, -7, 10.5, -14));
    }

    SUBCASE("Multiplying a tuple by a fraction") {
        Tuple4 a(1, -2, 3, -4);
        CHECK_EQ(a * 0.5f, Tuple4(0.5, -1, 1.5, -2));
    }

    SUBCASE("Dividing a tuple by a scalar") {
        Tuple4 a(1, -2, 3, -4);
        CHECK_EQ((a / 2).value(), Tuple4(0.5, -1, 1.5, -2));
    }

    SUBCASE("Computing the magnitude of vector(1, 0, 0)") {
        auto v = Tuple4::vector(1, 0, 0);
        CHECK_EQ(v.magnitude(), 1);
    }
    SUBCASE("Computing the magnitude of vector(0, 1, 0)") {
        auto v = Tuple4::vector(0, 1, 0);
        CHECK_EQ(v.magnitude(), 1);
    }
    SUBCASE("Computing the magnitude of vector(0, 0, 1)") {
        auto v = Tuple4::vector(0, 0, 1);
        CHECK_EQ(v.magnitude(), 1);
    }
    SUBCASE("Computing the magnitude of vector(1, 2, 3)") {
        auto v = Tuple4::vector(1, 2, 3);
        CHECK(compareFloat(v.magnitude(), std::sqrt(14)));
    }
    SUBCASE("Computing the magnitude of vector(-1, -2, -3)") {
        auto v = Tuple4::vector(-1, -2, -3);
        CHECK(compareFloat(v.magnitude(), std::sqrt(14)));
    }

    SUBCASE("Normalizing vector(0, 0, 0) gives None") {
        auto v = Tuple4::vector(0, 0, 0);
        CHECK_EQ(v.normalize(), std::nullopt);
    }
    SUBCASE("Normalizing vector(4, 0, 0) gives (1, 0, 0)") {
        auto v = Tuple4::vector(4, 0, 0);
        CHECK_EQ(v.normalize().value(), Tuple4::vector(1, 0, 0));
    }
    SUBCASE("Normalizing vector(1, 2, 3)") {
        auto v = Tuple4::vector(1, 2, 3);
        CHECK_EQ(v.normalize().value(), Tuple4::vector(0.267261f, 0.534522f, 0.801784f));
    }
    SUBCASE("The magnitude of a normalized vector") {
        auto v = Tuple4::vector(1, 2, 3);
        auto norm = v.normalize().value();
        CHECK(compareFloat(norm.magnitude(), 1.0f));
    }

    SUBCASE("The dot product of two tuples") {
        auto a = Tuple4::vector(1, 2, 3);
        auto b = Tuple4::vector(2, 3, 4);
        CHECK(compareFloat(a.dot(b), 20.f));
    }

    SUBCASE("The cross product of two vectors") {
        auto a = Tuple4::vector(1, 2, 3);
        auto b = Tuple4::vector(2, 3, 4);
        CHECK_EQ(a.cross(b), Tuple4::vector(-1, 2, -1));
        CHECK_EQ(b.cross(a), Tuple4::vector(1, -2, 1));
    }

}