#pragma once
#include <cstdint>
namespace LimitLit
{
struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    constexpr Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
    constexpr uint32_t Pack() const
    {
        return (static_cast<uint32_t>(a) << 24) |
               (static_cast<uint32_t>(r) << 16) |
               (static_cast<uint32_t>(g) << 8) |
               static_cast<uint32_t>(b);
    }
};
}
