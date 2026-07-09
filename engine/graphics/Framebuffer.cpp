#include "limitlit/graphics/Framebuffer.hpp"

#include <algorithm>

namespace LimitLit
{

Framebuffer::Framebuffer(
    int width,
    int height)
    :
    m_width(width),
    m_height(height),
    m_pixels(static_cast<std::size_t>(width * height))
{
}

void Framebuffer::Clear(
    uint32_t color)
{
    std::fill(
        m_pixels.begin(),
        m_pixels.end(),
        color);
}

void Framebuffer::SetPixel(
    int x,
    int y,
    uint32_t color)
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
