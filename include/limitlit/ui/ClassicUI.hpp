#pragma once
#include "limitlit/input/MouseState.hpp"
namespace LimitLit
{
class Framebuffer;
class ClassicUI
{
public:
    void Draw(Framebuffer& framebuffer, const MouseState& mouse);
private:
    struct Rect { int x; int y; int width; int height; };
    void DrawMenuBar(Framebuffer& framebuffer);
    void DrawStatusBar(Framebuffer& framebuffer, const char* status);
    void DrawSidePanels(Framebuffer& framebuffer, const MouseState& mouse);
    void DrawViewport(Framebuffer& framebuffer);
    void DrawBeveledPanel(Framebuffer& framebuffer, int x, int y, int width, int height);
    void DrawButton(Framebuffer& framebuffer, int x, int y, int width, int height, const char* label, bool hovered, bool pressed);
    bool Contains(const Rect& rect, int x, int y) const;
};
}
