#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <sstream>

#include "math/matrix.hpp"

TEST_CASE("Matrix") {

    SUBCASE("Multiplying two matrices") {
        Matrix4 A = {
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 8, 7, 6},
                {5, 4, 3, 2}
        };
        Matrix4 B = {
                {-2, 1, 2, 3},
                {3,  2, 1, -1},
                {4,  3, 6, 5},
                {1,  2, 7, 8}
        };
        Matrix4 C = {
                {20, 22, 50,  48},
                {44, 54, 114, 108},
                {40, 58, 110, 102},
                {16, 26, 46,  42}
        };
        CHECK_EQ(A * B, C);
    }

    SUBCASE("A matrix multiplied by a tuple") {
        Matrix4 A = {
                {1, 2, 3, 4},
                {2, 4, 4, 2},
                {8, 6, 4, 1},
                {0, 0, 0, 1}
        };
        Tuple4 b(1, 2, 3, 1);

        CHECK_EQ(A * b, Tuple4(18, 24, 33, 1));
    }

    SUBCASE("An identity matrix") {
        Matrix4 id = Matrix4::identity();
        for (size_t i = 0; i < id.matrixSize(); i++) {
            CHECK_EQ(id.at(i, i), 1);
        }
    }

    SUBCASE("Multiplying a matrix by the identity matrix") {
        Matrix4 A = {
                {1, 2, 3, 4},
                {2, 4, 4, 2},
                {8, 6, 4, 1},
                {0, 0, 0, 1}
        };
        Matrix4 I = Matrix4::identity();
        CHECK_EQ(A * I, A);
    }

    SUBCASE("A matrix multiplied by a tuple") {
        Matrix4 I = Matrix4::identity();
        Tuple4 b(1, 2, 3, 1);
        CHECK_EQ(I * b, b);
    }

    SUBCASE("Transposing a matrix") {
        Matrix4 A = {
                {0, 9, 3, 0},
                {9, 8, 0, 8},
                {1, 8, 5, 3},
                {0, 0, 5, 8}
        };
        Matrix4 At = {
                {0, 9, 1, 0},
                {9, 8, 8, 0},
                {3, 0, 5, 5},
                {0, 8, 3, 8}
        };
        CHECK_EQ(A.transpose(), At);
    }

    SUBCASE("Transposing an identity matrix") {
        Matrix4 I = Matrix4::identity();
        CHECK_EQ(I.identity(), I);
    }

    SUBCASE("Calculating the determinant of a matrix 2x2") {
        Matrix2 A = {
                {1,  5},
                {-3, 2}
        };
        CHECK(compareFloat(A.determinant(), 17.0f));
    }

    SUBCASE("A submatrix of a 3x3 matrix is a 2x2 matrix") {
        Matrix3 A = {
                {1,  5, 0},
                {-3, 2, 7},
                {0,  6, -3}
        };
        Matrix2 subA = {
                {-3, 2},
                {0,  6}
        };
        CHECK_EQ(A.subMatrix(0, 2).value(), subA);
    }

    SUBCASE("A submatrix of a 4x4 matrix is a 3x3 matrix") {
        Matrix4 A = {
                {-6, 1, 1,  6},
                {-8, 5, 8,  6},
                {-1, 0, 8,  2},
                {-7, 1, -1, 1}
        };
        Matrix3 subA = {
                {-6, 1,  6},
                {-8, 8,  6},
                {-7, -1, 1}
        };
        CHECK_EQ(A.subMatrix(2, 1).value(), subA);
    }

    SUBCASE("Calculating a minor of a 3x3 matrix") {
        Matrix3 A = {
                {3, 5,  0},
                {2, -1, -7},
                {6, -1, 5}
        };
        auto B = A.subMatrix(1, 0).value();
        CHECK(compareFloat(B.determinant(), A.minor(1, 0).value()));
    }

    SUBCASE("Calculating a cofactor of 3x3 matrix") {
        Matrix3 A = {
                {3, 5,  0},
                {2, -1, -7},
                {6, -1, 5}
        };

        CHECK(compareFloat(A.minor(0, 0).value(), -12.f));
        CHECK(compareFloat(A.cofactor(0, 0).value(), -12.f));
        CHECK(compareFloat(A.minor(1, 0).value(), 25.f));
        CHECK(compareFloat(A.cofactor(1, 0).value(), -25.f));
    }

    SUBCASE("Calculating the determinant of 3x3 matrix") {
        Matrix3 A = {
                {1,  2, 6},
                {-5, 8, -4},
                {2,  6, 4}
        };
        CHECK(compareFloat(A.determinant(), -196.0f));
    }

    SUBCASE("Calculating the determinant of 4x4 matrix") {
        Matrix4 A = {
                {-2, -8, 3,  5},
                {-3, 1,  7,  3},
                {1,  2,  -9, 6},
                {-6, 7,  7,  -9}
        };
        CHECK(compareFloat(A.determinant(), -4071.0f));
    }

    SUBCASE("Testing an invertible matrix for invertibility") {
        Matrix4 A = {
                {6, 4,  4, 4},
                {5, 5,  7, 6},
                {4, -9, 3, -7},
                {9, 1,  7, -6}
        };
        CHECK(compareFloat(A.determinant(), -2120));
        CHECK(A.isInvertible());
    }

    SUBCASE("Testing a noninvertible matrix for invertibility") {
        Matrix4 A = {
                {-4, 2, -2, -3},
                {9, 6, 2, 6},
                {0, -5, 1, -5},
                {0, 0, 0, 0}
        };
        CHECK(compareFloat(A.determinant(), 0.f));
        CHECK(!A.isInvertible());
    }

    SUBCASE("Verifying inverse property") {
        Matrix4 A = {
                {8,  -5, 9,  2},
                {7,  5,  6,  1},
                {-6, 0,  9,  6},
                {-3, 0,  -9, -4}
        };
        // A * A^-1 = I
        CHECK_EQ(A.inverse().value() * A, A.identity());
    }

    SUBCASE("Calculating the inverse of a matrix") {
        Matrix4 A = {
                {8,  -5, 9,  2},
                {7,  5,  6,  1},
                {-6, 0,  9,  6},
                {-3, 0,  -9, -4}
        };

        Matrix4 invA = {
                { -0.15385 , -0.15385 , -0.28205 , -0.53846 },
                { -0.07692 , 0.12308 , 0.02564 , 0.03077 },
                { 0.35897 , 0.35897 , 0.43590 , 0.92308 },
                { -0.69231 , -0.69231 , -0.76923 , -1.92308 }
        };

        CHECK_EQ(A.inverse().value(), invA);
    }

    SUBCASE("Multiplying a product by its inverse") {
        Matrix4 A = {
                {3, -9, 7, 3},
                {3, -8, 2, -9},
                {-4, 4, 4, 1},
                {-6, 5, -1, 1}
        };
        Matrix4 B = {
                {8, 2, 2, 2},
                {3, -1, 7, 0},
                {7, 0, 5, 4},
                {6, -2, 0, 5}
        };
        auto C = A * B;
        CHECK_EQ(C * B.inverse().value(), A);
    }

}

