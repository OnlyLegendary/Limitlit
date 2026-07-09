#include "limitlit/ui/ClassicUI.hpp"

#include "limitlit/graphics/Color.hpp"
#include "limitlit/graphics/Framebuffer.hpp"

namespace LimitLit
{

namespace
{
constexpr Color Background(58, 58, 58);
constexpr Color Panel(112, 112, 112);
constexpr Color PanelDark(48, 48, 48);
constexpr Color PanelLight(190, 190, 190);
constexpr Color ButtonFace(132, 132, 132);
constexpr Color ButtonHover(154, 154, 154);
constexpr Color ButtonPressed(86, 86, 86);
constexpr Color Viewport(28, 31, 34);
constexpr Color ViewportGrid(42, 47, 52);
constexpr Color Text(230, 230, 230);
constexpr Color TextDark(18, 18, 18);
constexpr Color Status(90, 90, 90);
constexpr Color CursorWhite(245, 245, 245);
constexpr Color CursorBlack(8, 8, 8);
}

void ClassicUI::Draw(Framebuffer& framebuffer, const MouseState& mouse)
{
    framebuffer.Clear(Background.Pack());

    DrawMenuBar(framebuffer);
    DrawSidePanels(framebuffer, mouse);
    DrawViewport(framebuffer);

    const char* status = "STATUS: READY";

    if (mouse.x < 190)
    {
        status = "STATUS: OBJECT TOOLS";
    }
    else if (mouse.x > framebuffer.Width() - 258)
    {
        status = "STATUS: PROPERTIES";
    }
    else
    {
        status = "STATUS: VIEWPORT";
    }

    DrawStatusBar(framebuffer, status);
    DrawSoftwareCursor(framebuffer, mouse);
}

void ClassicUI::DrawMenuBar(Framebuffer& framebuffer)
{
    const int width = framebuffer.Width();

    framebuffer.FillRectangle(0, 0, width, 28, Panel.Pack());
    framebuffer.DrawLine(0, 27, width - 1, 27, PanelDark.Pack());

    framebuffer.DrawString(12, 9, "File", TextDark.Pack());
    framebuffer.DrawString(58, 9, "Edit", TextDark.Pack());
    framebuffer.DrawString(106, 9, "Create", TextDark.Pack());
    framebuffer.DrawString(178, 9, "Camera", TextDark.Pack());
    framebuffer.DrawString(250, 9, "Render", TextDark.Pack());
    framebuffer.DrawString(324, 9, "Help", TextDark.Pack());

    framebuffer.DrawString(width - 154, 9, "LimitLit 0.4", TextDark.Pack());
}

void ClassicUI::DrawStatusBar(Framebuffer& framebuffer, const char* status)
{
    const int height = framebuffer.Height();
    const int width = framebuffer.Width();

    framebuffer.FillRectangle(0, height - 28, width, 28, Status.Pack());
    framebuffer.DrawLine(0, height - 28, width - 1, height - 28, PanelLight.Pack());

    framebuffer.DrawString(12, height - 19, status, TextDark.Pack());
    framebuffer.DrawString(width - 258, height - 19, "Mouse UI active", TextDark.Pack());
}

void ClassicUI::DrawSidePanels(Framebuffer& framebuffer, const MouseState& mouse)
{
    const int height = framebuffer.Height();
    const int width = framebuffer.Width();

    DrawBeveledPanel(framebuffer, 8, 38, 170, height - 78);
    DrawBeveledPanel(framebuffer, width - 258, 38, 250, height - 78);

    framebuffer.DrawString(22, 52, "Objects", Text.Pack());

    const Rect sphere{22, 76, 140, 28};
    const Rect cube{22, 110, 140, 28};
    const Rect cone{22, 144, 140, 28};
    const Rect terrain{22, 178, 140, 28};
    const Rect light{22, 212, 140, 28};
    const Rect camera{22, 246, 140, 28};

    DrawButton(framebuffer, sphere.x, sphere.y, sphere.width, sphere.height, "Sphere", Contains(sphere, mouse.x, mouse.y), mouse.leftDown && Contains(sphere, mouse.x, mouse.y));
    DrawButton(framebuffer, cube.x, cube.y, cube.width, cube.height, "Cube", Contains(cube, mouse.x, mouse.y), mouse.leftDown && Contains(cube, mouse.x, mouse.y));
    DrawButton(framebuffer, cone.x, cone.y, cone.width, cone.height, "Cone", Contains(cone, mouse.x, mouse.y), mouse.leftDown && Contains(cone, mouse.x, mouse.y));
    DrawButton(framebuffer, terrain.x, terrain.y, terrain.width, terrain.height, "Terrain", Contains(terrain, mouse.x, mouse.y), mouse.leftDown && Contains(terrain, mouse.x, mouse.y));
    DrawButton(framebuffer, light.x, light.y, light.width, light.height, "Light", Contains(light, mouse.x, mouse.y), mouse.leftDown && Contains(light, mouse.x, mouse.y));
    DrawButton(framebuffer, camera.x, camera.y, camera.width, camera.height, "Camera", Contains(camera, mouse.x, mouse.y), mouse.leftDown && Contains(camera, mouse.x, mouse.y));

    framebuffer.DrawString(width - 238, 52, "Properties", Text.Pack());

    const Rect material{width - 238, 76, 216, 28};
    const Rect sun{width - 238, 110, 216, 28};
    const Rect sky{width - 238, 144, 216, 28};

    DrawButton(framebuffer, material.x, material.y, material.width, material.height, "Material: Stone", Contains(material, mouse.x, mouse.y), mouse.leftDown && Contains(material, mouse.x, mouse.y));
    DrawButton(framebuffer, sun.x, sun.y, sun.width, sun.height, "Sun: Enabled", Contains(sun, mouse.x, mouse.y), mouse.leftDown && Contains(sun, mouse.x, mouse.y));
    DrawButton(framebuffer, sky.x, sky.y, sky.width, sky.height, "Sky: Classic", Contains(sky, mouse.x, mouse.y), mouse.leftDown && Contains(sky, mouse.x, mouse.y));
}

void ClassicUI::DrawViewport(Framebuffer& framebuffer)
{
    const int width = framebuffer.Width();
    const int height = framebuffer.Height();

    const int x = 190;
    const int y = 38;
    const int w = width - 468;
    const int h = height - 78;

    DrawBeveledPanel(framebuffer, x, y, w, h);

    framebuffer.FillRectangle(x + 10, y + 30, w - 20, h - 40, Viewport.Pack());
    framebuffer.DrawRectangle(x + 10, y + 30, w - 20, h - 40, PanelDark.Pack());

    framebuffer.DrawString(x + 16, y + 10, "Studio", Text.Pack());

    for (int gridX = x + 10; gridX < x + w - 10; gridX += 40)
    {
        framebuffer.DrawLine(gridX, y + 30, gridX, y + h - 11, ViewportGrid.Pack());
    }

    for (int gridY = y + 30; gridY < y + h - 10; gridY += 40)
    {
        framebuffer.DrawLine(x + 10, gridY, x + w - 11, gridY, ViewportGrid.Pack());
    }

    const int centerX = x + w / 2;
    const int centerY = y + h / 2;

    framebuffer.DrawLine(centerX, y + 30, centerX, y + h - 11, Color(72, 80, 88).Pack());
    framebuffer.DrawLine(x + 10, centerY, x + w - 11, centerY, Color(72, 80, 88).Pack());

    framebuffer.DrawString(centerX - 84, centerY - 28, "Welcome to LimitLit", Text.Pack(), 2);
    framebuffer.DrawString(centerX - 88, centerY + 6, "Create > Sphere", Color(180, 190, 200).Pack());
    framebuffer.DrawString(centerX - 88, centerY + 22, "Create > Terrain", Color(180, 190, 200).Pack());
}

void ClassicUI::DrawSoftwareCursor(Framebuffer& framebuffer, const MouseState& mouse)
{
    const int x = mouse.x;
    const int y = mouse.y;

    framebuffer.DrawLine(x, y, x, y + 16, CursorWhite.Pack());
    framebuffer.DrawLine(x, y, x + 10, y + 10, CursorWhite.Pack());
    framebuffer.DrawLine(x, y + 16, x + 4, y + 12, CursorWhite.Pack());
    framebuffer.DrawLine(x + 10, y + 10, x + 4, y + 12, CursorWhite.Pack());

    framebuffer.SetPixel(x + 1, y + 1, CursorBlack.Pack());
}

void ClassicUI::DrawBeveledPanel(Framebuffer& framebuffer, int x, int y, int width, int height)
{
    framebuffer.FillRectangle(x, y, width, height, Panel.Pack());

    framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
    framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());
    framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
    framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());
}

void ClassicUI::DrawButton(Framebuffer& framebuffer, int x, int y, int width, int height, const char* label, bool hovered, bool pressed)
{
    Color face = ButtonFace;

    if (hovered)
    {
        face = ButtonHover;
    }

    if (pressed)
    {
        face = ButtonPressed;
    }

    framebuffer.FillRectangle(x, y, width, height, face.Pack());

    if (pressed)
    {
        framebuffer.DrawLine(x, y, x + width - 1, y, PanelDark.Pack());
        framebuffer.DrawLine(x, y, x, y + height - 1, PanelDark.Pack());
        framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelLight.Pack());
        framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelLight.Pack());
        framebuffer.DrawString(x + 9, y + 11, label, TextDark.Pack());
    }
    else
    {
        framebuffer.DrawLine(x, y, x + width - 1, y, PanelLight.Pack());
        framebuffer.DrawLine(x, y, x, y + height - 1, PanelLight.Pack());
        framebuffer.DrawLine(x, y + height - 1, x + width - 1, y + height - 1, PanelDark.Pack());
        framebuffer.DrawLine(x + width - 1, y, x + width - 1, y + height - 1, PanelDark.Pack());
        framebuffer.DrawString(x + 8, y + 10, label, TextDark.Pack());
    }
}

bool ClassicUI::Contains(const Rect& rect, int x, int y) const
{
    return
        x >= rect.x &&
        y >= rect.y &&
        x < rect.x + rect.width &&
        y < rect.y + rect.height;
}

}
