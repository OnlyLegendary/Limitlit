#pragma once

#include <SDL2/SDL.h>
#include <cstdint>

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

    int Width() const;
    int Height() const;

private:
    void Destroy();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

    int m_width;
    int m_height;
};

}
