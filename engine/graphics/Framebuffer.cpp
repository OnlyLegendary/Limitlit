#include "limitlit/graphics/Framebuffer.hpp"

#include <algorithm>
#include <cstdlib>

namespace LimitLit
{

Framebuffer::Framebuffer(int width, int height)
    :
    m_width(width),
    m_height(height),
    m_pixels(static_cast<std::size_t>(width * height))
{
}

void Framebuffer::Clear(uint32_t color)
{
    std::fill(m_pixels.begin(), m_pixels.end(), color);
}

void Framebuffer::SetPixel(int x, int y, uint32_t color)
{
    if (x < 0 || y < 0)
    {
        return;
    }

    if (x >= m_width || y >= m_height)
    {
        return;
    }

    const int index = y * m_width + x;
    m_pixels[static_cast<std::size_t>(index)] = color;
}

void Framebuffer::DrawLine(int x0, int y0, int x1, int y1, uint32_t color)
{
    const int dx = std::abs(x1 - x0);
    const int sx = x0 < x1 ? 1 : -1;

    const int dy = -std::abs(y1 - y0);
    const int sy = y0 < y1 ? 1 : -1;

    int error = dx + dy;

    while (true)
    {
        SetPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        const int doubledError = 2 * error;

        if (doubledError >= dy)
        {
            error += dy;
            x0 += sx;
        }

        if (doubledError <= dx)
        {
            error += dx;
            y0 += sy;
        }
    }
}

void Framebuffer::DrawRectangle(int x, int y, int width, int height, uint32_t color)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    DrawLine(x, y, x + width - 1, y, color);
    DrawLine(x, y, x, y + height - 1, color);
    DrawLine(x + width - 1, y, x + width - 1, y + height - 1, color);
    DrawLine(x, y + height - 1, x + width - 1, y + height - 1, color);
}

void Framebuffer::FillRectangle(int x, int y, int width, int height, uint32_t color)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    for (int row = y; row < y + height; ++row)
    {
        for (int column = x; column < x + width; ++column)
        {
            SetPixel(column, row, color);
        }
    }
}

const uint32_t* Framebuffer::Data() const
{
    return m_pixels.data();
}

int Framebuffer::Width() const
{
    return m_width;
}

int Framebuffer::Height() const
{
    return m_height;
}

}
