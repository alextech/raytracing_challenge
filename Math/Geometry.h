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

inline tuple position(const Ray ray, const float distance)
{
    return ray.origin + ray.direction * distance;
}
