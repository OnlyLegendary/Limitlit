#include "limitlit/math/Vec3.hpp"
#include <cmath>
namespace LimitLit
{
Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
Vec3::Vec3(float xValue, float yValue, float zValue) : x(xValue), y(yValue), z(zValue) {}
Vec3 Vec3::operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
Vec3 Vec3::operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
Vec3 Vec3::operator*(float scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
Vec3 Vec3::operator/(float scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }
float Vec3::Dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
float Vec3::Length() const { return std::sqrt(Dot(*this)); }
Vec3 Vec3::Normalized() const
{
    const float length = Length();
    if (length <= 0.00001f) return Vec3();
    return *this / length;
}
}
