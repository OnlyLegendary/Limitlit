#include "limitlit/Renderer.hpp"
namespace LimitLit
{
Renderer::Renderer(int width, int height) : m_framebuffer(width, height), m_ui() {}
void Renderer::Render(const MouseState& mouse)
{
    m_ui.Draw(m_framebuffer, mouse);
}
const Framebuffer& Renderer::GetFramebuffer() const
{
    return m_framebuffer;
}
}
