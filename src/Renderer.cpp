#include "limitlit/Renderer.hpp"

#include "limitlit/graphics/Color.hpp"

namespace LimitLit
{

namespace
{
constexpr Color Background(58, 58, 58);
constexpr Color Panel(112, 112, 112);
constexpr Color PanelDark(64, 64, 64);
constexpr Color PanelLight(188, 188, 188);
constexpr Color Viewport(36, 38, 40);
constexpr Color StatusBar(96, 96, 96);
constexpr Color ButtonFace(132, 132, 132);
}

Renderer::Renderer(int width, int height)
    :
    m_framebuffer(width, height)
{
}

void Renderer::Render()
{
    m_framebuffer.Clear(Background.Pack());
    DrawEditorShell();
}

const Framebuffer& Renderer::GetFramebuffer() const
{
    return m_framebuffer;
}

void Renderer::DrawEditorShell()
{
    const int width = m_framebuffer.Width();
    const int height = m_framebuffer.Height();

    m_framebuffer.FillRectangle(0, 0, width, 28, Panel.Pack());
    m_framebuffer.DrawLine(0, 27, width - 1, 27, PanelDark.Pack());

    m_framebuffer.FillRectangle(0, height - 28, width, 28, StatusBar.Pack());
    m_framebuffer.DrawLine(0, height - 28, width - 1, height - 28, PanelLight.Pack());

    DrawBeveledPanel(8, 38, 160, height - 78);
    DrawBeveledPanel(width - 248, 38, 240, height - 78);
    DrawBeveledPanel(178, 38, width - 436, height - 78);

    m_framebuffer.FillRectangle(188, 48, width - 456, height - 98, Viewport.Pack());
    m_framebuffer.DrawRectangle(188, 48, width - 456, height - 98, PanelDark.Pack());

    DrawButton(16, 46, 140, 32);
    DrawButton(16, 86, 140, 32);
    DrawButton(16, 126, 140, 32);
    DrawButton(16, 166, 140, 32);
    DrawButton(width - 236, 46, 216, 32);
    DrawButton(width - 236, 86, 216, 32);

    m_framebuffer.DrawLine(218, 78, width - 308, height - 110, Color(92, 96, 102).Pack());
    m_framebuffer.DrawLine(width - 308, 78, 218, height - 110, Color(92, 96, 102).Pack());

    const int centerX = width / 2;
    const int centerY = height / 2;
    m_framebuffer.FillRectangle(centerX - 16, centerY - 16, 32, 32, Color(210, 210, 210).Pack());
    m_framebuffer.DrawRectangle(centerX - 16, centerY - 16, 32, 32, PanelLight.Pack());
    m_framebuffer.DrawRectangle(centerX - 15, centerY - 15, 30, 30, PanelDark.Pack());
}

void Renderer::DrawBeveledPanel(int x, int y, int width, int height)
{
    m_framebuffer.FillRectangle(x, y, width, height, Panel.Pack());

    m_framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
    m_framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());

    m_framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
    m_framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());
}

void Renderer::DrawButton(int x, int y, int width, int height)
{
    m_framebuffer.FillRectangle(x, y, width, height, ButtonFace.Pack());

    m_framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
    m_framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());

    m_framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
    m_framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());
}

}
