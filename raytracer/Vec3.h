#pragma once
#include <cmath>
#include <iostream>

class Vec3
{
public:
    inline static constexpr size_t CHANNELS = 3;

    Vec3() : m_e{ 0, 0, 0 } {}
    Vec3(double x, double y, double z) : m_e{ x, y, z } {}

    inline double x() const { return m_e[0]; }
    inline double y() const { return m_e[1]; }
    inline double z() const { return m_e[2]; }

    inline double r() const { return m_e[0]; }
    inline double g() const { return m_e[1]; }
    inline double b() const { return m_e[2]; }

    Vec3 operator-() const { return Vec3(-m_e[0], -m_e[1], -m_e[2]); }
    double operator[](int i) const { return m_e[i]; }
    double& operator[](int i) { return m_e[i]; }

    Vec3& operator+=(const Vec3& v) {
        m_e[0] += v.m_e[0];
        m_e[1] += v.m_e[1];
        m_e[2] += v.m_e[2];
        return *this;
    }

    Vec3& operator*=(const double s) {
        m_e[0] *= s;
        m_e[1] *= s;
        m_e[2] *= s;
        return *this;
    }

    Vec3& operator/=(const double s) {
        m_e[0] /= s;
        m_e[1] /= s;
        m_e[2] /= s;
        return *this;
    }

    Vec3& normalize() {
        auto len = length();
        m_e[0] /= len;
        m_e[1] /= len;
        m_e[2] /= len;
        return *this;
    }

    inline double length_squared() const {
        return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
    }
    inline double length() const {
        return std::sqrt(length_squared());
    }

    inline void copy_bytes(uint8_t* buffer) {
        buffer[0] = static_cast<uint8_t>(255.99 * m_e[0]);
        buffer[1] = static_cast<uint8_t>(255.99 * m_e[1]);
        buffer[2] = static_cast<uint8_t>(255.99 * m_e[2]);
    }

private:
    double m_e[3];
};

typedef Vec3 Point3;
typedef Vec3 Color;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v[0] << "," << v[1] << "," << v[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(const Vec3& u, double s) {
    return Vec3(u[0] * s, u[1] * s, u[2] * s);
}
inline Vec3 operator*(double s, const Vec3& u) {
    return Vec3(u[0] * s, u[1] * s, u[2] * s);
}

inline Vec3 operator/(const Vec3& u, double s) {
    return Vec3(u[0] / s, u[1] / s, u[2] / s);
}

inline double dot(const Vec3& u, const Vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
    return Vec3(u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]);
}

inline Vec3 normalized(const Vec3& v) {
    return v / v.length();
}