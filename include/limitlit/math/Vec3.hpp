#pragma once
namespace LimitLit
{
class Vec3
{
public:
    float x; float y; float z;
    Vec3();
    Vec3(float xValue, float yValue, float zValue);
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator/(float scalar) const;
    float Dot(const Vec3& other) const;
    float Length() const;
    Vec3 Normalized() const;
};
}
