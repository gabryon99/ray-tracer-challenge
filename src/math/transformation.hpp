#ifndef RAYTRACERCHALLENGE_TRANSFORMATION_HPP
#define RAYTRACERCHALLENGE_TRANSFORMATION_HPP

#include "matrix.hpp"

namespace transformation {

    [[nodiscard]] Matrix4 translation(float x, float y, float z) {

        /**
         * Translation matrix
         * | 1 0 0 x |
         * | 0 1 0 y |
         * | 0 0 1 z |
         * | 0 0 0 1 |
         */

        auto translationMatrix = Matrix4::identity();
        translationMatrix.set(0, Matrix4::SIZE - 1, x);
        translationMatrix.set(1, Matrix4::SIZE - 1, y);
        translationMatrix.set(2, Matrix4::SIZE - 1, z);
        return translationMatrix;
    }

    [[nodiscard]] constexpr Matrix4 scale(float x, float y, float z) {
        return {
                {x, 0, 0, 0},
                {0, y, 0, 0},
                {0, 0, z, 0},
                {0, 0, 0, 1}
        };
    }

    [[nodiscard]] constexpr Matrix4 rotationX(float r) {
        return {
                {1, 0,      0,       0},
                {0, cos(r), -sin(r), 0},
                {0, sin(r), cos(r),  0},
                {0, 0,      0,       1}
        };
    }

    [[nodiscard]] constexpr Matrix4 rotationY(float r) {
        return {
                {cos(r),  0, sin(r), 0},
                {0,       1, 0,      0},
                {-sin(r), 0, cos(r), 0},
                {0,       0, 0,      1}
        };
    }

    [[nodiscard]] constexpr Matrix4 rotationZ(float r) {
        return {
                {cos(r), -sin(r), 0, 0},
                {sin(r), cos(r),  0, 0},
                {0,      0,       1, 0},
                {0,      0,       0, 1}
        };
    }

    [[nodiscard]] constexpr Matrix4 shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
        return {
                {1, xy, xz, 0},
                {yx, 1, yz, 0},
                {zx, zy, 1, 0},
                {0, 0, 0, 1}
        };
    }

}

#endif //RAYTRACERCHALLENGE_TRANSFORMATION_HPP
