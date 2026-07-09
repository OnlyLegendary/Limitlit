#include "limitlit/Renderer.hpp"

#include "limitlit/graphics/Color.hpp"

namespace LimitLit
{

Renderer::Renderer(
    int width,
    int height)
    :
    m_framebuffer(width, height)
{
}

void Renderer::Render()
{
    const Color background(64, 64, 64);
    const Color lightGray(180, 180, 180);
    const Color darkGray(32, 32, 32);

    m_framebuffer.Clear(background.Pack());

    const int width = m_framebuffer.Width();
    const int height = m_framebuffer.Height();

    for (int x = 0; x < width; ++x)
    {
        m_framebuffer.SetPixel(x, 0, lightGray.Pack());
        m_framebuffer.SetPixel(x, height - 1, darkGray.Pack());
    }

    for (int y = 0; y < height; ++y)
    {
        m_framebuffer.SetPixel(0, y, lightGray.Pack());
        m_framebuffer.SetPixel(width - 1, y, darkGray.Pack());
    }

    const int centerX = width / 2;
    const int centerY = height / 2;

    for (int y = centerY - 8; y <= centerY + 8; ++y)
    {
        for (int x = centerX - 8; x <= centerX + 8; ++x)
        {
            m_framebuffer.SetPixel(x, y, Color(230, 230, 230).Pack());
        }
    }
}

const Framebuffer& Renderer::GetFramebuffer() const
{
    return m_framebuffer;
}

}
