#include "limitlit/Window.hpp"

#include "limitlit/graphics/Framebuffer.hpp"

namespace LimitLit
{

Window::Window()
    :
    m_window(nullptr),
    m_renderer(nullptr),
    m_texture(nullptr),
    m_mouse()
{
}

Window::~Window()
{
    Destroy();
}

bool Window::Create(const char* title, int width, int height)
{
    m_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN);

    if (!m_window)
    {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    SDL_ShowCursor(SDL_DISABLE);

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_renderer)
    {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        Destroy();
        return false;
    }

    m_texture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height);

    if (!m_texture)
    {
        SDL_Log("SDL_CreateTexture failed: %s", SDL_GetError());
        Destroy();
        return false;
    }

    return true;
}

bool Window::PollEvents()
{
    m_mouse.leftClicked = false;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            return false;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            m_mouse.x = event.motion.x;
            m_mouse.y = event.motion.y;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            m_mouse.leftDown = true;
            m_mouse.leftClicked = true;
            m_mouse.x = event.button.x;
            m_mouse.y = event.button.y;
        }

        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
        {
            m_mouse.leftDown = false;
            m_mouse.x = event.button.x;
            m_mouse.y = event.button.y;
        }
    }

    return true;
}

void Window::Present(const Framebuffer& framebuffer)
{
    SDL_UpdateTexture(
        m_texture,
        nullptr,
        framebuffer.Data(),
        framebuffer.Width() * static_cast<int>(sizeof(uint32_t)));

    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}

const MouseState& Window::GetMouseState() const
{
    return m_mouse;
}

void Window::Destroy()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

}
