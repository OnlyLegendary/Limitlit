#pragma once

#include <cstdint>

namespace LimitLit
{

class Framebuffer;

class BitmapFont
{
public:
    static void DrawCharacter(
        Framebuffer& framebuffer,
        int x,
        int y,
        char character,
        uint32_t color);

    static void DrawString(
        Framebuffer& framebuffer,
        int x,
        int y,
        const char* text,
        uint32_t color);
};

}
