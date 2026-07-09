#pragma once

#include "limitlit/graphics/Framebuffer.hpp"

namespace LimitLit
{

class Renderer
{
public:
    Renderer(int width, int height);

    void Render();

    const Framebuffer& GetFramebuffer() const;

private:
    void DrawEditorShell();
    void DrawBeveledPanel(int x, int y, int width, int height);
    void DrawButton(int x, int y, int width, int height, const char* label);
    void DrawViewportGrid();

private:
    Framebuffer m_framebuffer;
};

}
