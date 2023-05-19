#ifndef RAYTRACERCHALLENGE_MATRIX_HPP
#define RAYTRACERCHALLENGE_MATRIX_HPP

#include "utility.hpp"
#include "tuple.hpp"

#include <initializer_list>
#include <ostream>

template<size_t MATRIX_SIZE = 4>
class Matrix {

    static_assert(MATRIX_SIZE != 0, "Matrix size 0x0 are not allowed!");

private:
    std::array<float, MATRIX_SIZE * MATRIX_SIZE> data{0};
    size_t size = MATRIX_SIZE;
public:

    constexpr explicit Matrix() = default;

    constexpr Matrix(std::initializer_list<std::initializer_list<float>> values) {

        if (values.size() != MATRIX_SIZE) {
            throw std::runtime_error("Cannot instantiate matrix. Input matrix size is wrong.");
        }

        size_t x = 0, y = 0;
        for (auto row: values) {
            y = 0;
            for (auto cell : row) {
                set(x, y, cell);
                y += 1;
            }
            x += 1;
        }
    }

    static Matrix<MATRIX_SIZE> identity() {
        Matrix<MATRIX_SIZE> id;
        for (size_t i = 0; i < id.size; i++) {
            id.set(i, i, 1.f);
        }
        return id;
    }

    [[nodiscard]] bool isInvertible() const {
        return !compareFloat(determinant(), 0);
    }

    [[nodiscard]] float determinant() const {

        float det = 0;

        for (size_t col = 0; col < size; col++) {
            det += at(0, col) * cofactor(0, col).value();
        }

        return det;
    }

    [[nodiscard]] std::optional<float> minor(size_t row, size_t col) const {
        if (auto B = subMatrix(row, col)) {
            return B->determinant();
        }
        return {};
    }

    [[nodiscard]] std::optional<float> cofactor(size_t row, size_t col) const {

        if (auto minorOpt = minor(row, col)) {

            auto matrixMinor = *minorOpt;
            if (((row + col) & 1) == 1) {
                matrixMinor = -matrixMinor;
            }

            return matrixMinor;
        }

        return {};
    }

    [[nodiscard]] std::optional<Matrix<MATRIX_SIZE - 1>> subMatrix(size_t row, size_t col) const {

        if (row >= size || col >= size) {
            return {};
        }

        Matrix<MATRIX_SIZE - 1> sub;
        size_t si = 0, sj = 0;

        // Remove row `row` and col `col`
        for (size_t i = 0; i < size; i++) {
            if (i == row) continue;
            sj = 0;
            for (size_t j = 0; j < size; j++) {
                if (j == col) continue;
                sub.set(si, sj, at(i, j));
                sj++;
            }
            si++;
        }

        return sub;
    }

    [[nodiscard]] Matrix<MATRIX_SIZE> transpose() const {
        Matrix<MATRIX_SIZE> transposed;

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                transposed.set(i, j, at(j, i));
            }
        }

        return transposed;
    }

    [[nodiscard]] std::optional<Matrix<MATRIX_SIZE>> inverse() const {

        auto det = determinant();
        if (det == 0) return {};

        Matrix<MATRIX_SIZE> inv;

        for (size_t row = 0; row < size; row++) {
            for (size_t col = 0; col < size; col++) {
                auto c = cofactor(row, col).value();
                inv.set(col, row, c / det);
            }
        }

        return inv;
    }

    [[nodiscard]] float at(size_t x, size_t y) const { return data[x * MATRIX_SIZE + y]; }

    [[nodiscard]] size_t matrixSize() const { return size; }

    void set(size_t x, size_t y, float value) {
        data[x * MATRIX_SIZE + y] = value;
    }

    bool operator==(const Matrix<MATRIX_SIZE> &rhs) const {
        for (size_t i = 0; i < size; i++) {
            if (!compareFloat(data[i], rhs.data[i])) return false;
        }
        return true;
    }

    bool operator!=(const Matrix &rhs) const {
        return rhs != *this;
    }

    Matrix<MATRIX_SIZE> operator-() const {

        Matrix<MATRIX_SIZE> result;

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.set(i, j, -at(i, j));
            }
        }

        return result;
    }

    Matrix<MATRIX_SIZE> operator+(const Matrix<MATRIX_SIZE> &rhs) const {

        Matrix<MATRIX_SIZE> result;

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.set(i, j, rhs.at(i, j) + at(i, j));
            }
        }

        return result;
    }

    Matrix<MATRIX_SIZE> operator-(const Matrix<MATRIX_SIZE> &rhs) const {

        Matrix<MATRIX_SIZE> result;

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.set(i, j, rhs.at(i, j) - at(i, j));
            }
        }

        return result;
    }

    Matrix<MATRIX_SIZE> operator*(const Matrix &rhs) const {
        Matrix<MATRIX_SIZE> result;

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                for (size_t k = 0; k < size; k++) {
                    float curr = result.at(i, j);
                    result.set(i, j, curr + at(i, k) * rhs.at(k, j));
                }
            }
        }

        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {

        for (std::size_t i = 0; i < m.size; i++) {
            for (std::size_t j = 0; j < m.size; j++) {
                os << m.at(i, j) << " ";
            }
            os << "\n";
        }

        return os;
    }

};



using Matrix4 = Matrix<4>;
using Matrix3 = Matrix<3>;
using Matrix2 = Matrix<2>;

template<>
float Matrix2::determinant() const {

    float a = at(0, 0);
    float b = at(0, 1);
    float c = at(1, 0);
    float d = at(1, 1);

    return a * d - b * c;
}


/***
 * Multiply a matrix for a column vector.
 * @param m The matrix to multiply.
 * @param rhs The vector to multiply with.
 * @return A new column vector, as the multiplication result.
 */
Tuple4 operator*(const Matrix4& m, const Tuple4& rhs) {

    float x = 0, y = 0, z = 0, w = 0;
    x = m.at(0, 0) * rhs.x + m.at(0, 1) * rhs.y + m.at(0, 2) * rhs.z + m.at(0, 3) * rhs.w;
    y = m.at(1, 0) * rhs.x + m.at(1, 1) * rhs.y + m.at(1, 2) * rhs.z + m.at(1, 3) * rhs.w;
    z = m.at(2, 0) * rhs.x + m.at(2, 1) * rhs.y + m.at(2, 2) * rhs.z + m.at(2, 3) * rhs.w;
    w = m.at(3, 0) * rhs.x + m.at(3, 1) * rhs.y + m.at(3, 2) * rhs.z + m.at(3, 3) * rhs.w;

    return {x, y, z, w};
}

#endif //RAYTRACERCHALLENGE_MATRIX_HPP
