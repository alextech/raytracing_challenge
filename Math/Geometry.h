#pragma once

using namespace rt_math;

struct Ray
{

public:
    Ray(const tuple origin, const tuple direction)
    : m_origin(origin), m_direction(direction) {}

    tuple &origin = m_origin;
    tuple &direction = m_direction;

private:
    tuple m_origin;
    tuple m_direction;
};

struct Sphere
{
public:
    Sphere();
    tuple &origin = m_origin;
    [[nodiscard]]
    std::vector<float> intersects(const Ray &) const;
private:
    tuple m_origin;
};


inline tuple position(const Ray ray, const float distance)
{
    return ray.origin + ray.direction * distance;
}


inline Sphere::Sphere()
{
    m_origin = point(0, 0, 0);
}

[[nodiscard]]
inline std::vector<float> Sphere::intersects(const Ray &ray) const
{
    // vector from the sphere's center, to the ray origin
    // sphere is centered at the world origin
    const tuple sphere_to_ray = ray.origin - point(0, 0, 0);
    const float a = dot(ray.direction, ray.direction);
    const float b = 2 * dot(ray.direction, sphere_to_ray);
    const float c = dot(sphere_to_ray, sphere_to_ray) - 1;

    const float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return std::vector<float>(0);
    }

    return std::vector<float>
    {
        (-b - std::sqrt(discriminant)) / (2 * a),
        (-b + std::sqrt(discriminant)) / (2 * a)
    };
}
