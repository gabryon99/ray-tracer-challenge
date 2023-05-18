#ifndef RAYTRACERCHALLENGE_TUPLE4_HPP
#define RAYTRACERCHALLENGE_TUPLE4_HPP

#include <ostream>
#include <optional>

#include "utility.hpp"

struct Tuple4 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
    float w{0.0f};

    Tuple4(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} {
    }

    friend bool operator==(const Tuple4 &c1, const Tuple4 &c2) {
        return compareFloat(c1.x, c2.x) &&
               compareFloat(c1.y, c2.y) &&
               compareFloat(c1.z, c2.z) &&
               compareFloat(c1.w, c2.w);
    }

    friend std::ostream &operator<<(std::ostream &os, const Tuple4 &tuple4) {
        os << "Tuple4(x: " << tuple4.x << " y: " << tuple4.y << " z: " << tuple4.z << " w: " << tuple4.w << ")";
        return os;
    }

    friend Tuple4 operator+(const Tuple4 &c1, const Tuple4 &c2) {
        return {c1.x + c2.x, c1.y + c2.y, c1.z + c2.z, c1.w + c2.w};
    }

    friend Tuple4 operator-(const Tuple4 &c1) {
        return {-c1.x, -c1.y, -c1.z, -c1.w};
    }

    friend Tuple4 operator-(const Tuple4 &c1, const Tuple4 &c2) {
        return {c1.x - c2.x, c1.y - c2.y, c1.z - c2.z, c1.w - c2.w};
    }

    friend Tuple4 operator*(const Tuple4& c1, const float scalar) {
        return {c1.x * scalar, c1.y * scalar, c1.z * scalar, c1.w * scalar};
    }

    float dot(const Tuple4& c1) const {
        return ((c1.x * x )+ (c1.y * y) + (c1.z * z) + (c1.w * w));
    }

    Tuple4 cross(const Tuple4& b) const {
        // Returns a new vector that is perpendicular to `this` and `b`
        return Tuple4::vector(y * b.z - z * b.y,
                              z * b.x - x * b.z,
                              x * b.y - y * b.x);
    }

    friend std::optional<Tuple4> operator/(const Tuple4& c1, const float scalar) {
        if (scalar == 0) return {};
        return std::optional<Tuple4>({c1.x / scalar, c1.y / scalar, c1.z / scalar, c1.w / scalar});
    }

    float magnitude() const {
        return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
    }

    [[nodiscard]] std::optional<Tuple4> normalize() const {
        auto norm = magnitude();
        if (norm == 0) { return {}; }
        return std::optional<Tuple4>({x / norm, y / norm, z / norm, w / norm});
    }

    static Tuple4 point(float x, float y, float z) {
        return {x, y, z, 1.0f};
    }

    static Tuple4 vector(float x, float y, float z) {
        return {x, y, z, 0.0f};
    }

    [[nodiscard]]
    bool isPoint() const { return this->w == 1.0f; }

    [[nodiscard]]
    bool isVector() const { return this->w == 0.0f; }
};



#endif //RAYTRACERCHALLENGE_TUPLE4_HPP
