#include "limitlit/Renderer.hpp"

#include "limitlit/graphics/BitmapFont.hpp"
#include "limitlit/graphics/Color.hpp"

namespace LimitLit
{

namespace
{
constexpr Color Background(58, 58, 58);
constexpr Color Panel(112, 112, 112);
constexpr Color PanelDark(64, 64, 64);
constexpr Color PanelLight(188, 188, 188);
constexpr Color Viewport(31, 34, 36);
constexpr Color StatusBar(96, 96, 96);
constexpr Color ButtonFace(132, 132, 132);
constexpr Color Text(225, 225, 225);
constexpr Color TextDark(20, 20, 20);
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

    BitmapFont::DrawString(m_framebuffer, 12, 10, "File", TextDark.Pack());
    BitmapFont::DrawString(m_framebuffer, 62, 10, "Edit", TextDark.Pack());
    BitmapFont::DrawString(m_framebuffer, 116, 10, "Create", TextDark.Pack());
    BitmapFont::DrawString(m_framebuffer, 194, 10, "Camera", TextDark.Pack());
    BitmapFont::DrawString(m_framebuffer, 270, 10, "Render", TextDark.Pack());
    BitmapFont::DrawString(m_framebuffer, 346, 10, "Help", TextDark.Pack());

    m_framebuffer.FillRectangle(0, height - 28, width, 28, StatusBar.Pack());
    m_framebuffer.DrawLine(0, height - 28, width - 1, height - 28, PanelLight.Pack());
    BitmapFont::DrawString(m_framebuffer, 12, height - 18, "Status: Ready", TextDark.Pack());
    BitmapFont::DrawString(m_framebuffer, width - 250, height - 18, "LimitLit v0.3.0", TextDark.Pack());

    DrawBeveledPanel(8, 38, 160, height - 78);
    DrawBeveledPanel(width - 248, 38, 240, height - 78);
    DrawBeveledPanel(178, 38, width - 436, height - 78);

    BitmapFont::DrawString(m_framebuffer, 20, 50, "Objects", Text.Pack());
    BitmapFont::DrawString(m_framebuffer, width - 234, 50, "Properties", Text.Pack());

    DrawButton(18, 82, 136, 30, "Sphere");
    DrawButton(18, 120, 136, 30, "Cube");
    DrawButton(18, 158, 136, 30, "Cone");
    DrawButton(18, 196, 136, 30, "Terrain");
    DrawButton(18, 234, 136, 30, "Light");
    DrawButton(18, 272, 136, 30, "Camera");

    DrawButton(width - 234, 82, 210, 30, "Material: Stone");
    DrawButton(width - 234, 120, 210, 30, "Sun: Enabled");
    DrawButton(width - 234, 158, 210, 30, "Sky: Classic");

    m_framebuffer.FillRectangle(188, 48, width - 456, height - 98, Viewport.Pack());
    m_framebuffer.DrawRectangle(188, 48, width - 456, height - 98, PanelDark.Pack());

    DrawViewportGrid();

    BitmapFont::DrawString(
        m_framebuffer,
        width / 2 - 120,
        height / 2 - 6,
        "Viewport: no scene loaded",
        Color(160, 164, 168).Pack());
}

void Renderer::DrawViewportGrid()
{
    const int width = m_framebuffer.Width();
    const int height = m_framebuffer.Height();

    const int x = 188;
    const int y = 48;
    const int w = width - 456;
    const int h = height - 98;

    const int centerX = x + w / 2;
    const int centerY = y + h / 2;

    for (int gx = x + 40; gx < x + w; gx += 40)
    {
        m_framebuffer.DrawLine(gx, y, gx, y + h - 1, Color(40, 43, 46).Pack());
    }

    for (int gy = y + 40; gy < y + h; gy += 40)
    {
        m_framebuffer.DrawLine(x, gy, x + w - 1, gy, Color(40, 43, 46).Pack());
    }

    m_framebuffer.DrawLine(centerX, y, centerX, y + h - 1, Color(74, 78, 84).Pack());
    m_framebuffer.DrawLine(x, centerY, x + w - 1, centerY, Color(74, 78, 84).Pack());
}

void Renderer::DrawBeveledPanel(int x, int y, int width, int height)
{
    m_framebuffer.FillRectangle(x, y, width, height, Panel.Pack());

    m_framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
    m_framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());

    m_framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
    m_framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());
}

void Renderer::DrawButton(int x, int y, int width, int height, const char* label)
{
    m_framebuffer.FillRectangle(x, y, width, height, ButtonFace.Pack());

    m_framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
    m_framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());

    m_framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
    m_framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());

    BitmapFont::DrawString(m_framebuffer, x + 10, y + 11, label, TextDark.Pack());
}

}
