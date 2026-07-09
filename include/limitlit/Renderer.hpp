#pragma once

#include "limitlit/graphics/Framebuffer.hpp"

namespace LimitLit
{

class Renderer
{
public:
    Renderer(
        int width,
        int height);

    void Render();

    const Framebuffer& GetFramebuffer() const;

private:
    Framebuffer m_framebuffer;
};

}
