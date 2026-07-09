#include "limitlit/ui/ClassicUI.hpp"
#include "limitlit/graphics/Color.hpp"
#include "limitlit/graphics/Framebuffer.hpp"
#include "limitlit/render/RayTracer.hpp"

namespace LimitLit
{
namespace
{
constexpr Color Background(50, 52, 52);
constexpr Color Panel(116, 113, 106);
constexpr Color PanelDark(42, 42, 40);
constexpr Color PanelLight(205, 199, 185);
constexpr Color PanelMid(92, 91, 86);
constexpr Color ButtonFace(142, 140, 132);
constexpr Color ButtonHover(164, 162, 150);
constexpr Color ButtonPressed(78, 78, 74);
constexpr Color Accent(78, 104, 122);
constexpr Color AccentDark(38, 58, 72);
constexpr Color Text(238, 234, 220);
constexpr Color TextDark(12, 13, 14);
constexpr Color Status(76, 78, 76);
}

void ClassicUI::Draw(Framebuffer& framebuffer, const MouseState& mouse)
{
    framebuffer.Clear(Background.Pack());
    DrawMenuBar(framebuffer);
    DrawSidePanels(framebuffer, mouse);
    DrawViewport(framebuffer);

    const char* status = "STATUS: SPHERE TOOL SELECTED";
    if (mouse.x < 190) status = "STATUS: OBJECT PALETTE";
    else if (mouse.x > framebuffer.Width() - 258) status = "STATUS: SPHERE PROPERTIES";
    else status = "STATUS: CPU RAY VIEW";

    DrawStatusBar(framebuffer, status);
}

void ClassicUI::DrawMenuBar(Framebuffer& framebuffer)
{
    const int width = framebuffer.Width();
    framebuffer.FillRectangle(0, 0, width, 30, Panel.Pack());
    framebuffer.DrawLine(0, 29, width - 1, 29, PanelDark.Pack());
    framebuffer.DrawLine(0, 30, width - 1, 30, PanelLight.Pack());

    framebuffer.DrawString(12, 10, "File", TextDark.Pack());
    framebuffer.DrawString(58, 10, "Edit", TextDark.Pack());
    framebuffer.DrawString(106, 10, "Create", TextDark.Pack());
    framebuffer.DrawString(178, 10, "Camera", TextDark.Pack());
    framebuffer.DrawString(250, 10, "Render", TextDark.Pack());
    framebuffer.DrawString(324, 10, "Help", TextDark.Pack());

    framebuffer.FillRectangle(width - 176, 5, 150, 19, Accent.Pack());
    framebuffer.DrawRectangle(width - 176, 5, 150, 19, AccentDark.Pack());
    framebuffer.DrawString(width - 164, 11, "LimitLit 0.8", Text.Pack());
}

void ClassicUI::DrawStatusBar(Framebuffer& framebuffer, const char* status)
{
    const int height = framebuffer.Height();
    const int width = framebuffer.Width();

    framebuffer.FillRectangle(0, height - 32, width, 32, Status.Pack());
    framebuffer.DrawLine(0, height - 32, width - 1, height - 32, PanelLight.Pack());
    framebuffer.DrawLine(0, height - 31, width - 1, height - 31, PanelDark.Pack());

    framebuffer.DrawString(14, height - 22, status, Text.Pack());
    framebuffer.FillRectangle(width - 292, height - 26, 270, 20, PanelMid.Pack());
    framebuffer.DrawRectangle(width - 292, height - 26, 270, 20, PanelDark.Pack());
    framebuffer.DrawString(width - 280, height - 20, "RENDER MODE: CPU CLASSIC", Text.Pack());
}

void ClassicUI::DrawSidePanels(Framebuffer& framebuffer, const MouseState& mouse)
{
    const int height = framebuffer.Height();
    const int width = framebuffer.Width();

    DrawBeveledPanel(framebuffer, 8, 42, 170, height - 86, true);
    DrawBeveledPanel(framebuffer, width - 258, 42, 250, height - 86, true);

    DrawSectionTitle(framebuffer, 22, 58, "Objects");

    const Rect sphere{22, 88, 140, 30};
    const Rect cube{22, 124, 140, 30};
    const Rect cone{22, 160, 140, 30};
    const Rect terrain{22, 196, 140, 30};
    const Rect light{22, 232, 140, 30};
    const Rect camera{22, 268, 140, 30};

    DrawButton(framebuffer, sphere.x, sphere.y, sphere.width, sphere.height, "Sphere", Contains(sphere, mouse.x, mouse.y), mouse.leftDown && Contains(sphere, mouse.x, mouse.y), true);
    DrawButton(framebuffer, cube.x, cube.y, cube.width, cube.height, "Cube", Contains(cube, mouse.x, mouse.y), mouse.leftDown && Contains(cube, mouse.x, mouse.y));
    DrawButton(framebuffer, cone.x, cone.y, cone.width, cone.height, "Cone", Contains(cone, mouse.x, mouse.y), mouse.leftDown && Contains(cone, mouse.x, mouse.y));
    DrawButton(framebuffer, terrain.x, terrain.y, terrain.width, terrain.height, "Terrain", Contains(terrain, mouse.x, mouse.y), mouse.leftDown && Contains(terrain, mouse.x, mouse.y));
    DrawButton(framebuffer, light.x, light.y, light.width, light.height, "Light", Contains(light, mouse.x, mouse.y), mouse.leftDown && Contains(light, mouse.x, mouse.y));
    DrawButton(framebuffer, camera.x, camera.y, camera.width, camera.height, "Camera", Contains(camera, mouse.x, mouse.y), mouse.leftDown && Contains(camera, mouse.x, mouse.y));

    DrawSectionTitle(framebuffer, 22, 330, "Scene");
    framebuffer.FillRectangle(22, 356, 140, 84, PanelMid.Pack());
    framebuffer.DrawRectangle(22, 356, 140, 84, PanelDark.Pack());
    framebuffer.DrawString(32, 368, "Sun", Text.Pack());
    framebuffer.DrawString(32, 388, "Camera", Text.Pack());
    framebuffer.DrawString(32, 408, "Sphere 01", Text.Pack());

    DrawSectionTitle(framebuffer, width - 238, 58, "Properties");
    DrawButton(framebuffer, width - 238, 88, 216, 30, "Object: Sphere", false, false, true);
    DrawButton(framebuffer, width - 238, 124, 216, 30, "Material: Ice", Contains({width - 238, 124, 216, 30}, mouse.x, mouse.y), false);
    DrawButton(framebuffer, width - 238, 160, 216, 30, "Shadows: On", false, false);
    DrawButton(framebuffer, width - 238, 196, 216, 30, "Haze: Soft", false, false);

    DrawSectionTitle(framebuffer, width - 238, 258, "Transform");
    framebuffer.FillRectangle(width - 238, 284, 216, 112, PanelMid.Pack());
    framebuffer.DrawRectangle(width - 238, 284, 216, 112, PanelDark.Pack());
    framebuffer.DrawString(width - 224, 300, "X  0.00", Text.Pack());
    framebuffer.DrawString(width - 224, 324, "Y  0.00", Text.Pack());
    framebuffer.DrawString(width - 224, 348, "Z  0.00", Text.Pack());
    framebuffer.DrawString(width - 224, 372, "R  0.85", Text.Pack());
}

void ClassicUI::DrawViewport(Framebuffer& framebuffer)
{
    const int width = framebuffer.Width();
    const int height = framebuffer.Height();
    const int x = 190;
    const int y = 42;
    const int w = width - 468;
    const int h = height - 86;

    DrawBeveledPanel(framebuffer, x, y, w, h, false);

    framebuffer.FillRectangle(x + 10, y + 8, w - 20, 22, AccentDark.Pack());
    framebuffer.DrawString(x + 20, y + 16, "RAY VIEW", Text.Pack());

    const int vx = x + 10;
    const int vy = y + 34;
    const int vw = w - 20;
    const int vh = h - 44;

    RayTracer tracer;
    tracer.RenderScene(framebuffer, vx, vy, vw, vh);

    framebuffer.DrawRectangle(vx, vy, vw, vh, PanelDark.Pack());
    framebuffer.DrawString(vx + 20, vy + 22, "CPU RAY TRACE  CONTACT SHADOW", Color(235,238,242).Pack());
}

void ClassicUI::DrawSectionTitle(Framebuffer& framebuffer, int x, int y, const char* title)
{
    framebuffer.FillRectangle(x - 4, y - 4, 128, 18, AccentDark.Pack());
    framebuffer.DrawString(x + 4, y + 2, title, Text.Pack());
}

void ClassicUI::DrawBeveledPanel(Framebuffer& framebuffer, int x, int y, int width, int height, bool active)
{
    const Color fill = active ? Panel : Color(106, 105, 100);
    framebuffer.FillRectangle(x, y, width, height, fill.Pack());
    framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
    framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());
    framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
    framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());
}

void ClassicUI::DrawButton(Framebuffer& framebuffer, int x, int y, int width, int height, const char* label, bool hovered, bool pressed, bool selected)
{
    Color face = selected ? Color(150, 164, 170) : ButtonFace;
    if (hovered) face = ButtonHover;
    if (pressed) face = ButtonPressed;

    framebuffer.FillRectangle(x, y, width, height, face.Pack());

    if (selected)
    {
        framebuffer.FillRectangle(x, y, 5, height, Accent.Pack());
    }

    if (pressed)
    {
        framebuffer.DrawLine(x, y, x + width - 1, y, PanelDark.Pack());
        framebuffer.DrawLine(x, y, x, y + height - 1, PanelDark.Pack());
        framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelLight.Pack());
        framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelLight.Pack());
        framebuffer.DrawString(x + 12, y + 12, label, TextDark.Pack());
    }
    else
    {
        framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
        framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());
        framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
        framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());
        framebuffer.DrawString(x + 11, y + 11, label, TextDark.Pack());
    }
}

bool ClassicUI::Contains(const Rect& rect, int x, int y) const
{
    return x >= rect.x && y >= rect.y && x < rect.x + rect.width && y < rect.y + rect.height;
}
}
