#pragma once

#include <SDL2/SDL.h>

namespace LimitLit
{

class Window
{
public:

    Window();

    ~Window();

    bool Create(
        const char* title,
        int width,
        int height);

    bool PollEvents();

    SDL_Renderer* Renderer();

private:

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

}
