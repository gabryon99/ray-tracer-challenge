#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <sstream>

#include "math/matrix.hpp"
#include "math/transformation.hpp"

TEST_CASE("Testing transformation matrices") {

    using namespace transformation;

    SUBCASE("Multiplying by a translation matrix") {
        auto transform = translation(5, -3, 2);
        auto p = point(-3, 4, 5);
        CHECK_EQ(transform * p, point(2, 1, 7));
    }

    SUBCASE("Multiplying by the inverse of the translation matrix") {
        auto transform = translation(5, -3, 2);
        auto inv = transform.inverse().value();
        auto p = point(-3, 4, 5);
        CHECK_EQ(inv * p, point(-8, 7, 3));
    }

    SUBCASE("Translation does not affect vectors") {
        auto transform = translation(5, -3, 2);
        auto v = vector(-3, 4, 5);
        CHECK_EQ(transform * v, v);
    }

    SUBCASE("A scaling matrix applied to a point") {
        auto transform = scale(2, 3, 4);
        auto p = point(-4, 6, 8);
        CHECK_EQ(transform * p, point(-8, 18, 32));
    }

    SUBCASE("A scaling matrix applied to a vector") {
        auto transform = scale(2, 3, 4);
        auto v = vector(-4, 6, 8);
        CHECK_EQ(transform * v, vector(-8, 18, 32));
    }

    SUBCASE("Multiplying by the inverse of a scaling matrix") {
        auto transform = scale(2, 3, 4);
        auto inv = transform.inverse().value();
        auto v = vector(-4, 6, 8);
        CHECK_EQ(inv * v, vector(-2, 2, 2));
    }

    SUBCASE("Reflection is scaling by a negative value") {
        auto transform = scale(-1, 1, 1);
        auto p = point(2, 3, 4);
        CHECK_EQ(transform * p, point(-2, 3, 4));
    }

    SUBCASE("Rotating a point around the x axis") {
        auto p = point(0, 1, 0);
        auto halfQuarter = rotationX(PI / 4);
        auto fullQuarter = rotationX(PI / 2);
        CHECK_EQ(halfQuarter * p, point(0, SQR_TWO / 2, SQR_TWO / 2));
        CHECK_EQ(fullQuarter * p, point(0, 0, 1));
    }

    SUBCASE("The inverse of an x-rotation rotates in the opposite direction") {
        auto p = point(0, 1, 0);
        auto halfQuarter = rotationX(PI / 4);
        auto inv = halfQuarter.inverse().value();
        CHECK_EQ(inv * p, point(0, SQR_TWO / 2, -SQR_TWO / 2));
    }

    SUBCASE("Rotating a point around the y axis") {
        auto p = point(0, 0, 1);
        auto halfQuarter = rotationY(PI / 4);
        auto fullQuarter = rotationY(PI / 2);
        CHECK_EQ(halfQuarter * p, point(SQR_TWO / 2, 0, SQR_TWO / 2));
        CHECK_EQ(fullQuarter * p, point(1, 0, 0));
    }

    SUBCASE("Rotating a point around the z axis") {
        auto p = point(0, 1, 0);
        auto halfQuarter = rotationZ(PI / 4);
        auto fullQuarter = rotationZ(PI / 2);
        CHECK_EQ(halfQuarter * p, point(-SQR_TWO / 2, SQR_TWO / 2, 0));
        CHECK_EQ(fullQuarter * p, point(-1, 0, 0));
    }

    SUBCASE("A shearing transformation moves x in proportion to y") {
        auto transform = shearing(1, 0, 0, 0, 0, 0);
        auto p = point(2, 3, 4);
        CHECK_EQ(transform * p, point(5, 3, 4));
    }

    SUBCASE("A shearing transformation moves x in proportion to z") {
        auto transform = shearing(0, 1, 0, 0, 0, 0);
        auto p = point(2, 3, 4);
        CHECK_EQ(transform * p, point(6, 3, 4));
    }

    SUBCASE("A shearing transformation moves y in proportion to x") {
        auto transform = shearing(0, 0, 1, 0, 0, 0);
        auto p = point(2, 3, 4);
        CHECK_EQ(transform * p, point(2, 5, 4));
    }

    SUBCASE("A shearing transformation moves y in proportion to z") {
        auto transform = shearing(0, 0, 0, 1, 0, 0);
        auto p = point(2, 3, 4);
        CHECK_EQ(transform * p, point(2, 7, 4));
    }

    SUBCASE("A shearing transformation moves z in proportion to x") {
        auto transform = shearing(0, 0, 0, 0, 1, 0);
        auto p = point(2, 3, 4);
        CHECK_EQ(transform * p, point(2, 3, 6));
    }

    SUBCASE("A shearing transformation moves z in proportion to y") {
        auto transform = shearing(0, 0, 0, 0, 0, 1);
        auto p = point(2, 3, 4);
        CHECK_EQ(transform * p, point(2, 3, 7));
    }


}

