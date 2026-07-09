#pragma once

#include <cstdint>
#include <vector>

namespace LimitLit
{

class Framebuffer
{
public:

    Framebuffer(
        int width,
        int height);

    void Clear(uint32_t color);

    void SetPixel(
        int x,
        int y,
        uint32_t color);

    [[nodiscard]]
    const uint32_t* Data() const;

    [[nodiscard]]
    int Width() const;

    [[nodiscard]]
    int Height() const;

private:

    int m_width;
    int m_height;

    std::vector<uint32_t> m_pixels;
};

}
