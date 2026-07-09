#include "limitlit/render/RayTracer.hpp"
#include "limitlit/graphics/Color.hpp"
#include "limitlit/math/Vec3.hpp"
#include "limitlit/render/Ray.hpp"

#include <algorithm>
#include <cmath>

namespace LimitLit
{
namespace
{
uint8_t ClampToByte(float value)
{
    value = std::clamp(value, 0.0f, 255.0f);
    return static_cast<uint8_t>(value);
}

bool HitSphere(const Ray& ray, const Vec3& center, float radius, float& hitDistance)
{
    const Vec3 oc = ray.origin - center;
    const float a = ray.direction.Dot(ray.direction);
    const float b = 2.0f * oc.Dot(ray.direction);
    const float c = oc.Dot(oc) - radius * radius;
    const float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f)
    {
        return false;
    }

    const float sqrtDiscriminant = std::sqrt(discriminant);
    const float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
    const float t1 = (-b + sqrtDiscriminant) / (2.0f * a);

    if (t0 > 0.001f)
    {
        hitDistance = t0;
        return true;
    }

    if (t1 > 0.001f)
    {
        hitDistance = t1;
        return true;
    }

    return false;
}
}

void RayTracer::RenderSphere(Framebuffer& framebuffer, int x, int y, int width, int height)
{
    const Vec3 cameraOrigin(0.0f, 0.0f, -3.0f);
    const Vec3 sphereCenter(0.0f, 0.0f, 0.0f);
    const float sphereRadius = 0.85f;

    const Vec3 lightDirection = Vec3(-0.7f, -1.0f, -0.8f).Normalized();
    const float aspect = static_cast<float>(width) / static_cast<float>(height);

    for (int py = 0; py < height; ++py)
    {
        for (int px = 0; px < width; ++px)
        {
            const float u = ((static_cast<float>(px) + 0.5f) / static_cast<float>(width)) * 2.0f - 1.0f;
            const float v = 1.0f - ((static_cast<float>(py) + 0.5f) / static_cast<float>(height)) * 2.0f;

            Ray ray;
            ray.origin = cameraOrigin;
            ray.direction = Vec3(u * aspect, v, 1.4f).Normalized();

            float hitDistance = 0.0f;

            if (HitSphere(ray, sphereCenter, sphereRadius, hitDistance))
            {
                const Vec3 hitPoint = ray.origin + ray.direction * hitDistance;
                const Vec3 normal = (hitPoint - sphereCenter).Normalized();

                const float diffuse = std::max(0.0f, normal.Dot(lightDirection * -1.0f));
                const float rim = std::pow(std::max(0.0f, 1.0f - normal.z), 2.0f);

                const float shade = 42.0f + diffuse * 170.0f + rim * 28.0f;

                const Color color(
                    ClampToByte(shade * 0.86f),
                    ClampToByte(shade * 0.92f),
                    ClampToByte(shade * 1.00f));

                framebuffer.SetPixel(x + px, y + py, color.Pack());
            }
        }
    }
}
}
