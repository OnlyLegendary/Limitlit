#pragma once

#include <vector>
#include <cstdint>

namespace LimitLit
{

class Framebuffer
{
public:

    Framebuffer(
        int width,
        int height);

    void Clear(
        uint32_t color);

    void SetPixel(
        int x,
        int y,
        uint32_t color);

    const uint32_t* Data() const;

    int Width() const;

    int Height() const;

private:

    int m_width;

    int m_height;

    std::vector<uint32_t> m_pixels;
};

}
