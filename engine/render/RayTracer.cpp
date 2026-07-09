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

Color Mix(const Color& a, const Color& b, float t)
{
    t = std::clamp(t, 0.0f, 1.0f);
    return Color(
        ClampToByte(static_cast<float>(a.r) * (1.0f - t) + static_cast<float>(b.r) * t),
        ClampToByte(static_cast<float>(a.g) * (1.0f - t) + static_cast<float>(b.g) * t),
        ClampToByte(static_cast<float>(a.b) * (1.0f - t) + static_cast<float>(b.b) * t));
}

bool HitSphere(const Ray& ray, const Vec3& center, float radius, float& hitDistance)
{
    const Vec3 oc = ray.origin - center;
    const float a = ray.direction.Dot(ray.direction);
    const float b = 2.0f * oc.Dot(ray.direction);
    const float c = oc.Dot(oc) - radius * radius;
    const float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f) return false;

    const float root = std::sqrt(discriminant);
    const float t0 = (-b - root) / (2.0f * a);
    const float t1 = (-b + root) / (2.0f * a);

    if (t0 > 0.001f) { hitDistance = t0; return true; }
    if (t1 > 0.001f) { hitDistance = t1; return true; }
    return false;
}

bool HitGround(const Ray& ray, float& hitDistance)
{
    if (std::fabs(ray.direction.y) < 0.0001f) return false;

    hitDistance = (-0.85f - ray.origin.y) / ray.direction.y;
    return hitDistance > 0.001f;
}

float ShadowAmount(const Vec3& point, const Vec3& lightDirection)
{
    Ray shadowRay;
    shadowRay.origin = point + lightDirection * 0.02f;
    shadowRay.direction = lightDirection;

    float distance = 0.0f;
    if (HitSphere(shadowRay, Vec3(0.0f, 0.0f, 0.0f), 0.85f, distance))
    {
        return 0.32f;
    }

    return 1.0f;
}

Color SkyColor(float v)
{
    const Color top(32, 66, 115);
    const Color horizon(118, 170, 220);
    return Mix(horizon, top, std::clamp(v, 0.0f, 1.0f));
}

Color GroundColor(const Vec3& point)
{
    const int gridX = static_cast<int>(std::floor(point.x * 2.0f));
    const int gridZ = static_cast<int>(std::floor(point.z * 2.0f));
    const bool grid = (gridX % 4 == 0) || (gridZ % 4 == 0);

    Color base(86, 80, 58);
    if (grid) base = Color(112, 104, 76);

    const float distanceFade = std::clamp((point.z + 2.0f) / 18.0f, 0.0f, 1.0f);
    return Mix(base, Color(150, 165, 170), distanceFade * 0.20f);
}
}

void RayTracer::RenderScene(Framebuffer& framebuffer, int x, int y, int width, int height)
{
    const Vec3 cameraOrigin(0.0f, 0.25f, -4.2f);
    const Vec3 sphereCenter(0.0f, 0.0f, 0.0f);
    const float sphereRadius = 0.85f;
    const Vec3 lightDirection = Vec3(-0.65f, 0.95f, -0.55f).Normalized();

    const float aspect = static_cast<float>(width) / static_cast<float>(height);

    for (int py = 0; py < height; ++py)
    {
        for (int px = 0; px < width; ++px)
        {
            const float u = ((static_cast<float>(px) + 0.5f) / static_cast<float>(width)) * 2.0f - 1.0f;
            const float v = 1.0f - ((static_cast<float>(py) + 0.5f) / static_cast<float>(height)) * 2.0f;

            Ray ray;
            ray.origin = cameraOrigin;
            ray.direction = Vec3(u * aspect, v * 0.85f - 0.05f, 1.35f).Normalized();

            Color pixel = SkyColor((v + 1.0f) * 0.5f);

            float sphereT = 0.0f;
            float groundT = 0.0f;
            const bool sphereHit = HitSphere(ray, sphereCenter, sphereRadius, sphereT);
            const bool groundHit = HitGround(ray, groundT);

            if (sphereHit && (!groundHit || sphereT < groundT))
            {
                const Vec3 hitPoint = ray.origin + ray.direction * sphereT;
                const Vec3 normal = (hitPoint - sphereCenter).Normalized();

                const float direct = std::max(0.0f, normal.Dot(lightDirection));
                const float skyAmbient = 0.24f + std::max(0.0f, normal.y) * 0.20f;
                const float groundBounce = std::max(0.0f, -normal.y) * 0.16f;
                const float rim = std::pow(std::max(0.0f, 1.0f - normal.z), 2.0f) * 0.15f;

                const float brightness = skyAmbient + direct * 0.72f + groundBounce + rim;

                Color sphereColor(
                    ClampToByte(120.0f * brightness),
                    ClampToByte(135.0f * brightness),
                    ClampToByte(150.0f * brightness));

                sphereColor = Mix(sphereColor, Color(95, 88, 64), groundBounce * 0.55f);

                const float haze = std::clamp((sphereT - 2.0f) / 9.0f, 0.0f, 1.0f);
                pixel = Mix(sphereColor, SkyColor(0.25f), haze * 0.10f);
            }
            else if (groundHit)
            {
                const Vec3 hitPoint = ray.origin + ray.direction * groundT;
                Color ground = GroundColor(hitPoint);

                const float shadow = ShadowAmount(hitPoint, lightDirection);
                ground = Color(
                    ClampToByte(static_cast<float>(ground.r) * shadow),
                    ClampToByte(static_cast<float>(ground.g) * shadow),
                    ClampToByte(static_cast<float>(ground.b) * shadow));

                const float haze = std::clamp((groundT - 2.0f) / 22.0f, 0.0f, 1.0f);
                pixel = Mix(ground, SkyColor(0.14f), haze);
            }

            framebuffer.SetPixel(x + px, y + py, pixel.Pack());
        }
    }

    framebuffer.FillCircle(x + width - 118, y + 80, 22, Color(240, 220, 132).Pack());
    framebuffer.FillCircle(x + width - 110, y + 73, 10, Color(255, 242, 168).Pack());
}
}
