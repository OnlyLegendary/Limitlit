#pragma once

#include "limitlit/graphics/Framebuffer.hpp"
#include "limitlit/input/MouseState.hpp"
#include "limitlit/ui/ClassicUI.hpp"

namespace LimitLit
{

class Renderer
{
public:
    Renderer(int width, int height);

    void Render(const MouseState& mouse);

    const Framebuffer& GetFramebuffer() const;

private:
    Framebuffer m_framebuffer;
    ClassicUI m_ui;
};

}
