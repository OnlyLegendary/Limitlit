#pragma once
#include "limitlit/input/MouseState.hpp"
#include <SDL2/SDL.h>
namespace LimitLit
{
class Framebuffer;
class Window
{
public:
    Window();
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    bool Create(const char* title, int width, int height);
    bool PollEvents();
    void Present(const Framebuffer& framebuffer);
    const MouseState& GetMouseState() const;
private:
    void Destroy();
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    MouseState m_mouse;
};
}
