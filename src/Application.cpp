#include "limitlit/Application.hpp"

#include "limitlit/Renderer.hpp"
#include "limitlit/Window.hpp"

#include <SDL2/SDL.h>

namespace LimitLit
{

int Application::Run()
{
    constexpr int windowWidth = 1280;
    constexpr int windowHeight = 720;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    Window window;

    if (!window.Create("LimitLit v0.1.0", windowWidth, windowHeight))
    {
        SDL_Quit();
        return 1;
    }

    Renderer renderer(windowWidth, windowHeight);

    bool running = true;

    while (running)
    {
        running = window.PollEvents();

        renderer.Render();

        window.Present(renderer.GetFramebuffer());

        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}

}
