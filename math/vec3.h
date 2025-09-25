//
// Created by kryst on 24/09/2025.
//

#ifndef MATH_VISUALIZER_VEC3_H
#define MATH_VISUALIZER_VEC3_H

#include <cmath>
#include <iostream>

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(const float x_, const float y_, const float z_) : x(x_), y(y_), z(z_) {}

    Vec3 operator+(const Vec3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
    Vec3 operator-(const Vec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
    Vec3 operator*(const float scalar) const   { return {x * scalar, y * scalar, z * scalar}; }
    Vec3 operator/(const float scalar) const   { return {x / scalar, y / scalar, z / scalar}; }

    [[nodiscard]] float dot(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    [[nodiscard]] float length() const { return std::sqrt(dot(*this)); }

    [[nodiscard]] Vec3 normalized() const {
        float len = length();
        return len > 0 ? *this / len : Vec3();
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    }
};

#endif
