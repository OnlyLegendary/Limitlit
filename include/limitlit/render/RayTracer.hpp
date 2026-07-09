#pragma once
#include "limitlit/graphics/Framebuffer.hpp"
namespace LimitLit
{
class RayTracer
{
public:
    void RenderSphere(Framebuffer& framebuffer, int x, int y, int width, int height);
};
}
