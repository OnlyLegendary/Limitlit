#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace LimitLit
{

class Framebuffer
{
public:
    Framebuffer(int width, int height);

    void Clear(uint32_t color);
    void SetPixel(int x, int y, uint32_t color);

    void DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
    void DrawRectangle(int x, int y, int width, int height, uint32_t color);
    void FillRectangle(int x, int y, int width, int height, uint32_t color);
    void FillCircle(int centerX, int centerY, int radius, uint32_t color);

    void DrawCharacter(int x, int y, char character, uint32_t color, int scale = 1);
    void DrawString(int x, int y, std::string_view text, uint32_t color, int scale = 1);

    const uint32_t* Data() const;

    int Width() const;
    int Height() const;

private:
    int m_width;
    int m_height;
    std::vector<uint32_t> m_pixels;
};

}
